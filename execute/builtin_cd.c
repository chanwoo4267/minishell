/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwopa <chanwopa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 16:37:09 by chanwopa          #+#    #+#             */
/*   Updated: 2023/01/20 18:57:33 by chanwopa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "execution_test.h"

static void	cd_change_envp(char *old_cwd, t_info *info)
{
	char	*str;
	char	*new_pwd;

	str = ft_strjoin("OLDPWD=", old_cwd);
	change_envp(str, info);
	free(str);
	str = getcwd(NULL, 0);
	new_pwd = ft_strjoin("PWD=", str);
	free(str);
	change_envp(new_pwd, info);
	free(new_pwd);
}

void	builtin_cd(t_list *list, t_info *info)
{
	char	*old_cwd;
	char	**command;

	command = list_to_strs(list);
	if (!command || !command[1])
	{
		free_strs(command);
		error_return("builtin_cd, no valid directory income");
	}
	else
	{
		old_cwd = getcwd(NULL, 0);
		if (chdir(command[1]) == -1)
		{
			g_status.global_exit_status = 1;
			error_return("builtin_cd, chdir fail");
		}
		else
			cd_change_envp(old_cwd, info);
		free(old_cwd);
	}
	free_strs(command);
}
