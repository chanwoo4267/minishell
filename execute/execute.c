/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwopa <chanwopa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 16:29:21 by chanwopa          #+#    #+#             */
/*   Updated: 2023/01/09 21:07:30 by chanwopa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"
#include "../minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define FAIL 0
#define SUCCESS 1

int	execute(t_commandlist **commandlist, t_info *info)
{
	t_list	*list;

	if (!commandlist || !commandlist[0]->command)
		print_error();
	if (!commandlist[1]->command)
		execute_subshell(commandlist[0], info);
	else
		execute_pipe(commandlist, info);
}

int	execute_subshell(t_commandlist *commandlist, t_info *info)
{
	if (commandlist->redirection)
		redirection(commandlist->redirection);
	if (commandlist->command)
	{
		if (execute_builtin(commandlist->command, info) == FAIL)
			execute_command(commandlist->command, info);
	}
	if (commandlist->redirection)
		reset_redirection(commandlist->redirection);
}

int	execute_pipe(t_commandlist **commandlist, t_info *info)
{
	
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
}
