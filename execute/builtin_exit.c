/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwopa <chanwopa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:11:07 by chanwopa          #+#    #+#             */
/*   Updated: 2023/01/23 05:41:36 by chanwopa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtin_exit(t_list *list)
{
	char	**command;

	command = list_to_strs(list);
	if (!command)
		system_error("malloc error", NULL, 1);
	else if (!command[1])
		exit(g_status.global_exit_status);
	else if (command[2])
	{
		print_error(command[0], "too many arguments", NULL, NO);
		free_strs(command);
		return ;
	}
	if (!ft_isnumeric(command[1]))
	{
		errno = 22;
		print_error(command[0], command[1], "numeric argument required", YES);
		exit(255);
	}
	g_status.global_exit_status = ft_atoi(command[1]);
	g_status.global_exit_status %= 256;
	if (g_status.global_exit_status < 0)
		g_status.global_exit_status += 256;
	free_strs(command);
	exit(g_status.global_exit_status);
}

/*
	exit 단일로 올 경우 현재 global status로 그대로 exit해준다.
	exit 뒤에 인자가 2개 이상 올 경우 오류를 출력해주고 exit하지 않는다.
	exit 뒤에 인자가 1개인 경우, 뒤의 인자가 숫자가 아니라면 
	errno = 22 (invalid argument) 오류 출력 후 exit(255)
	정상적인 숫자 인자라면 해당 수를 256으로 나눈 나머지로, 음수면 양수로 변환해서
*/