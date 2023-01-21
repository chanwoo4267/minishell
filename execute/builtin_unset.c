/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwopa <chanwopa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 15:52:49 by chanwopa          #+#    #+#             */
/*   Updated: 2023/01/21 15:02:53 by chanwopa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "execution_test.h"

void	builtin_unset(t_list *list, t_info *info)
{
	char	**command;
	int		i;

	command = list_to_strs(list);
	if (!command)
	{
		error_return("builtin_unset, list to strs error", 1);
		return ;
	}
	if (command[1])
	{
		i = 1;
		while (command[i])
		{
			if (!ft_strchr(command[i], '='))
				delete_envp(command[i], info);
			i++;
		}
	}
	free_strs(command);
}
