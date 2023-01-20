/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwopa <chanwopa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:11:51 by chanwopa          #+#    #+#             */
/*   Updated: 2023/01/20 19:11:31 by chanwopa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "execution_test.h"

static void	print_export_envp(t_info *info)
{
	int		i;
	char	*equal_loc;
	char	*temp;

	i = 0;
	while (info->envp[i])
	{
		printf("declare -x ");
		equal_loc = ft_strchr(info->envp[i], '=');
		if (!equal_loc)
			printf("%s\n", info->envp[i]);
		else
		{
			temp = ft_substr(info->envp[i], 0, equal_loc - info->envp[i] + 1);
			printf("%s\"%s\"\n", temp, equal_loc + 1);
			free(temp);
		}
		i++;
	}
}

static void	export_change_envp(char *command, t_info *info)
{
	char	*equal_loc;
	int		i;

	i = 0;
	equal_loc = ft_strchr(command, '=');
	if (equal_loc)
	{
		while (info->envp[i])
		{
			if (ft_strncmp(command, info->envp[i], equal_loc - command) == 0)
			{
				change_envp(command, info);
				return ;
			}
			i++;
		}
	}
	add_envp(command, info);
}

static void	export_all_inputs(char **command, t_info *info)
{
	int		i;
	char	*equal_loc;

	i = 0;
	while (command[++i])
	{
		equal_loc = ft_strchr(command[i], '=');
		if (equal_loc == command[i] || ft_isdigit(command[i][0]))
		{
			error_return("builtin_export, invalid argument to export");
			return ;
		}
		else
			export_change_envp(command[i], info);
	}
}

void	builtin_export(t_list *list, t_info *info)
{
	char	**command;
	char	*equal_loc;
	int		i;

	command = list_to_strs(list);
	if (!command)
	{
		error_return("builtin_export, list_to_strs error");
		return ;
	}
	if (!command[1])
		print_export_envp(info);
	else
		export_all_inputs(command, info);
	free_strs(command);
}
