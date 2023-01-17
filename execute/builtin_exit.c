/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwopa <chanwopa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:11:07 by chanwopa          #+#    #+#             */
/*   Updated: 2023/01/17 13:27:04 by chanwopa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "execution_test.h"

void	builtin_exit(t_list *list, t_info *info)
{
	char	**command;

	command = list_to_strs(list);
	if (!command)
		print_error("builtin_exit", "list_to_strs error");
	if (!command[1])
		exit(g_status.global_exit_status);
	if (!command[2])
		print_error("builtin_exit", "too many exit argument");
	if (!ft_isnumeric(command[1]))
		print_error("builtin_exit", "non-numeric exit argument");
	g_status.global_exit_status = ft_atoi(command[1]);
	g_status.global_exit_status %= 256;
	if (g_status.global_exit_status < 0)
		g_status.global_exit_status += 256;
	exit(g_status.global_exit_status);
}
