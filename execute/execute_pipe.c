/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwopa <chanwopa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 12:57:13 by chanwopa          #+#    #+#             */
/*   Updated: 2023/01/14 05:39:56 by chanwopa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "execution_test.h"

/*
	각 프로세스는 항상 실행되어야 함. 중간의 pipelined process가 예기치못하게 종료되어도
	뒤의 프로세스 역시 실행되어야 함. 따라서 메인 프로세스에서 exit_status는 항상
	마지막 프로세스의 exit status만 얻어서 이를 저장하면 된다.

static int	wait_piped_pids(pid_t *pids, int cmd_count)
{
	int	status;
	int	i;

	i = -1;
	while (++i < cmd_count)
	{
		if (i == cmd_count - 1)
		{
			if (waitpid(pids[i], &status, 0) < 0)
				print_error("wait_exit", "waitpid error final pc");
		}
		else
		{
			if (waitpid(pids[i], NULL, 0) < 0)
				print_error("wait_exit", "waitpid error");
		}
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (WTERMSIG(status));
	return (EXIT_FAILURE);
}
*/

static void	init_pipes(int cmd_count, pid_t **pids, int ***pipes)
{
	int	i;

	(*pids) = malloc(sizeof(pid_t) * cmd_count);
	(*pipes) = malloc(sizeof(int *) * (cmd_count - 1));
	if (!(*pids) || !(*pipes))
		print_error("init_pipes", "malloc error");
	i = -1;
	while (++i < cmd_count - 1)
	{
		(*pipes)[i] = malloc(sizeof(int) * 2);
		if (!((*pipes)[i]))
			print_error("init_pipes", "submalloc error");
	}
	if (ft_memset(*pids, 255, sizeof(pid_t) * cmd_count) != *pids)
		print_error("init_pipes", "memset error");
}

/*	
	pipes : (cmd_count - 1) 크기의 int[2] array
	cmd_count == 2 이라고 가정했을 때, pids는 
	0번째 프로세스는 pids[0][1]을 STDOUT으로 설정
	1번째 프로세스는 pids[0][0]을 STDIN으로 설정
*/
static void	set_pipeline(int child_index, int cmd_count, int ***pipes)
{
	int	i;

	i = -1;
	while (++i < cmd_count - 1)
	{
		if (i == child_index - 1)
		{
			if ((*pipes)[i][0] != STDIN_FILENO)
				if (dup2((*pipes)[i][0], STDIN_FILENO) != STDIN_FILENO)
					print_error("set_pipeline", "dup2 error on stdin");
		}
		else if (i == child_index)
		{
			if ((*pipes)[i][1] != STDOUT_FILENO)
				if (dup2((*pipes)[i][1], STDOUT_FILENO) != STDOUT_FILENO)
					print_error("set_pipeline", "dup2 error on stdout");
		}
	}
}

static void	build_pipeline(int cmd_count, pid_t **pids, int ***pipes)
{
	int	i;
	int	status;

	i = -1;
	while (++i < cmd_count - 1)
	{
		if (pipe((*pipes)[i]) < 0)
			print_error("build_pipeline", "pipe error");
	}
	i = -1;
	while (++i < cmd_count)
	{
		(*pids)[i] = fork();
		if ((*pids)[i] < 0)
			print_error("build_pipeline", "fork error");
		else if ((*pids)[i] == 0) /* 자식 프로세스는 pipeline 설정하고 바로 종료 */
		{
			set_pipeline(i, cmd_count, pipes);
			return ;
		}
		waitpid((*pids)[i], &status, 0);
	}
}

/*
	build_pipeline에서 fork()된 자식 프로세스는 set_pipeline 함수를 실행하여
	자신의 fd를 설정한 뒤, 곧바로 break하여 빠져나온다.
	따라서, index 0번부터 순회하다가 자신의 pid를 발견한다면 (pid == 0)
	해당하는 index의 command를 가지고 execute_subshell을 실행한다.
	이때 info->issubshell = YES 로 설정했으므로 자식프로세스는
	execute_subshell을 빠져나오지 못하고 exit한다.
*/
int	execute_pipe(t_commandlist *commandlist, t_info *info, int cmd_count)
{
	pid_t	*pids;
	int		**pipes;
	int		i;

	init_pipes(cmd_count, &pids, &pipes);
	build_pipeline(cmd_count, &pids, &pipes);
	i = -1;
	while (++i < cmd_count)
	{
		if (pids[i] == 0)
		{
			info->issubshell = YES;
			execute_subshell(commandlist[i], info, i);
		}
	}
	i = -1;
	while (++i < cmd_count - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		free(pipes[i]);
	}
	//g_status.global_exit_status = wait_piped_pids(pids, cmd_count);
	free(pipes);
	free(pids);
	return (0);
}
