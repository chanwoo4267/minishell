/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwopa <chanwopa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 15:52:55 by chanwopa          #+#    #+#             */
/*   Updated: 2023/01/21 13:41:34 by chanwopa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "execution_test.h"

void	builtin_env(t_list *list, t_info *info)
{
	char	**command;
	int		i;

	command = list_to_strs(list);
	if (!command || command[1])
	{
		error_return("builtin_env, invalid argument", 1);
	}
	else
	{
		i = -1;
		while (info->envp[++i])
		{
			if (ft_strchr(info->envp[i], '='))
			{
				printf("%s\n", info->envp[i]);
			}
		}
	}
	free_strs(command);
}
