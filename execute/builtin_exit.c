/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwopa <chanwopa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:11:07 by chanwopa          #+#    #+#             */
/*   Updated: 2023/01/20 19:20:16 by chanwopa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "execution_test.h"

void	builtin_exit(t_list *list)
{
	char	**command;

	command = list_to_strs(list);
	if (!command)
	{
		error_return("builtin_exit, list_to_strs error");
		return ;
	}
	if (!command[1])
	{
		free_strs(command);
		exit(g_status.global_exit_status);
	}
	if (!command[2])
	{
		g_status.global_exit_status = 1;
		error_return("builtin_exit, too many arguments");
		free_strs(command);
		return ;
	}
	if (!ft_isnumeric(command[1]))
	{
		errno = 22;
		error_return("builtin_exit, non-numeric argument");
		free_strs(command);
		exit(255);
	}
	g_status.global_exit_status = ft_atoi(command[1]);
	g_status.global_exit_status %= 256;
	if (g_status.global_exit_status < 0)
		g_status.global_exit_status += 256;
	free_strs(command);
	exit(g_status.global_exit_status);
}
