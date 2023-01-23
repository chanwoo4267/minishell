/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwopa <chanwopa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 16:40:05 by chanwopa          #+#    #+#             */
/*   Updated: 2023/01/24 01:55:39 by chanwopa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	free_deprecated_envp(char **envp)
{
	int	i;

	if (envp)
	{
		i = 0;
		while (envp[i])
		{
			free(envp[i]);
			i++;
		}
		free(envp);
	}
}

void	change_envp(char *new, t_info *info)
{
	int		i;
	char	*equal_loc;

	equal_loc = ft_strchr(new, '=');
	if (!equal_loc)
		return ;
	i = 0;
	while (info->envp[i])
	{
		if (ft_strncmp(new, info->envp[i], equal_loc - new) == 0)
		{
			free(info->envp[i]);
			info->envp[i] = ft_strdup(new);
		}
		i++;
	}
}

void	add_envp(char *new, t_info *info)
{
	char	**new_envp;
	int		i;

	i = 0;
	while (info->envp[i])
		i++;
	new_envp = malloc(sizeof(char *) * (i + 2));
	if (!new_envp)
		system_error("malloc error", NULL, 1);
	i = 0;
	while (info->envp[i])
	{
		new_envp[i] = ft_strdup(info->envp[i]);
		i++;
	}
	new_envp[i] = ft_strdup(new);
	i++;
	new_envp[i] = NULL;
	free_deprecated_envp(info->envp);
	info->envp = new_envp;
}

void	delete_envp(char *del, t_info *info)
{
	char	**new_envp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (info->envp[i])
		i++;
	new_envp = malloc(sizeof(char *) * i);
	if (!new_envp)
		system_error("malloc error", NULL, 1);
	i = -1;
	while (info->envp[++i])
	{
		if (ft_strncmp(del, info->envp[i], ft_strlen(del)) == 0 && \
			info->envp[i][ft_strlen(del)] == '=')
			continue ;
		new_envp[j] = ft_strdup(info->envp[i]);
		j++;
	}
	new_envp[j] = NULL;
	free_deprecated_envp(info->envp);
	info->envp = new_envp;
}

/*
	환경변수를 추가, 삭제, 해제, 변경 해주는 함수들
*/