/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwopa <chanwopa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 15:52:55 by chanwopa          #+#    #+#             */
/*   Updated: 2023/01/17 20:49:21 by chanwopa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "execution_test.h"

void	builtin_env(t_list *list, t_info *info)
{
	char	**command;
	int		i;

	command = list_to_strs(list);
	if (!command)
		print_error("builtin_env", "list_to_strs error");
	if (command[1])
	{
		free_strs(command);
		print_error("builtin_env", "env with argument");
	}
	else
	{
		i = 0;
		while (info->envp[i])
		{
			if (ft_strchr(info->envp[i], '='))
				printf("%s\n", info->envp[i]);
			i++;
		}
	}
	free_strs(command);
}
