/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwopa <chanwopa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 16:29:21 by chanwopa          #+#    #+#             */
/*   Updated: 2023/01/13 18:52:17 by chanwopa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "execution_test.h"

/*	parsing 부분에서 잘못된 input은 전부 걸러준다고 생각함.				*/
/*	이는 정상적으로 구성된 리스트로 구성됬고, 끝에 두 포인터가 NULL이며,	*/
/*	적어도 하나 이상의 command가 들어있다는 것을 보장함					*/
int	execute(t_commandlist *commandlist, t_info *info)
{
	int	command_count;

	command_count = get_commands_count(commandlist);
	if (command_count < 1)
		print_error("execute", "parsed input invalid");
	else if (command_count == 1)
		execute_subshell(commandlist[0], info);
	/*
	else
		execute_pipe(commandlist, info, command_count);
	*/
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

int	reset_redirection(t_info *info)
{
	if (info->fd[0] != STDIN_FILENO)
	{
		if (dup2(info->fd[0], STDIN_FILENO) != STDIN_FILENO)
			print_error("reset_redirection", "dup2 error for STDIN");
	}
	if (info->fd[1] != STDOUT_FILENO)
	{
		if (dup2(info->fd[1], STDOUT_FILENO) != STDOUT_FILENO)
			print_error("reset_redirection", "dup2 error for STDOUT");
	}
	if (info->fd[2] != STDERR_FILENO)
	{
		if (dup2(info->fd[2], STDERR_FILENO) != STDERR_FILENO)
			print_error("reset_redirection", "dup2 error for STDERR");
	}
	return (0);
}
