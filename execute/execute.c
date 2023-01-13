/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwopa <chanwopa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 16:29:21 by chanwopa          #+#    #+#             */
/*   Updated: 2023/01/13 12:59:14 by chanwopa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "execution_test.h"

/*	parsing 부분에서 잘못된 input은 전부 걸러준다고 생각함.				*/
/*	이는 정상적으로 구성된 리스트로 구성됬고, 끝에 두 포인터가 NULL이며,	*/
/*	적어도 하나 이상의 command가 들어있다는 것을 보장함					*/
int	execute(t_commandlist *commandlist, t_info *info)
{
	if (!commandlist[1].command)
		execute_subshell(commandlist[0], info);
	else
		execute_pipe(commandlist, info);
	return (0);
}

int	execute_subshell(t_commandlist commandlist, t_info *info)
{
	if (commandlist.redirection)
		redirection(commandlist.redirection);
	//if (execute_builtin(commandlist.command, info) == FAIL)
		execute_command(commandlist.command, info);
	if (info->issubshell == YES)
		exit(g_status.global_exit_status);
	if (commandlist.redirection)
		reset_redirection(info);
	return (0);
}

int	execute_pipe(t_commandlist *commandlist, t_info *info)
{
	commandlist[0].command = NULL;
	info->envp = NULL;
	return (0);
}

int	reset_redirection(t_info *info)
{
	if (info->fd[0] != STDIN_FILENO)
	{
		if (dup2(info->fd[0], STDIN_FILENO) != STDIN_FILENO)
			print_error();
	}
	if (info->fd[1] != STDOUT_FILENO)
	{
		if (dup2(info->fd[1], STDOUT_FILENO) != STDOUT_FILENO)
			print_error();
	}
	if (info->fd[2] != STDERR_FILENO)
	{
		if (dup2(info->fd[2], STDERR_FILENO) != STDERR_FILENO)
			print_error();
	}
	return (0);
}
