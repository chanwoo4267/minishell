/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwopa <chanwopa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:11:51 by chanwopa          #+#    #+#             */
/*   Updated: 2023/01/24 01:39:57 by chanwopa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	print_export_envp(t_info *info)
{
	int		i;
	char	*equal_loc;
	char	*temp;

	i = 0;
	while (info->envp[i])
	{
		equal_loc = ft_strchr(info->envp[i], '=');
		if (!equal_loc)
			printf("declare -x %s\n", info->envp[i]);
		else if (equal_loc - 1 == info->envp[i] && info->envp[i][0] == '_')
		{
			i++;
			continue ;
		}
		else
		{
			temp = ft_substr(info->envp[i], 0, equal_loc - info->envp[i] + 1);
			printf("declare -x %s\"%s\"\n", temp, equal_loc + 1);
			if (temp)
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
			errno = 22;
			print_error(command[0], command[i], "not a valid identifier", YES);
		}
		else
			export_change_envp(command[i], info);
	}
}

void	builtin_export(t_list *list, t_info *info)
{
	char	**command;

	command = list_to_strs(list);
	if (!command)
		system_error("malloc error", NULL, 1);
	if (!command[1])
		print_export_envp(info);
	else
		export_all_inputs(command, info);
	free_strs(command);
}

/*
	export 단일로 올 경우 print_export_envp 함수로 모든 환경변수와 쉘 변수 출력
	여러 인자가 주어질경우 각 인자를 export_all_inputs 함수로 환경변수 또는 쉘 변수에 등록
	인자에서 =이 있을경우 환경변수로 등록, 동일한 이름의 환경변수를 찾아 change_envp 호출
	동일한 이름이 없을경우 while문을 빠져나와 add_envp 호출, 새로운 환경변수 리스트를 만듬
	인자이 =가 없을 경우 바로 add_envp를 호출하여 새로운 환경변수 리스트를 만듬
*/