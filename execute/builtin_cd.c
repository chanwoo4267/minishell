/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwopa <chanwopa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 16:37:09 by chanwopa          #+#    #+#             */
/*   Updated: 2023/01/17 16:56:11 by chanwopa         ###   ########seoul.kr  */
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
	if (!command)
		print_error("builtin_cd", "list_to_strs error");
	if (!command[1])
	{
		free_strs(command);
		print_error("builtin_cd", "no_directory");
	}
	else
	{
		old_cwd = getcwd(NULL, 0);
		if (chdir(command[1]) == -1)
		{
			free_strs(command);
			print_error("builtin_cd", "cannot cd to dir");
		}
		else
			cd_change_envp(old_cwd, info);
		free(old_cwd);
	}
	free_strs(command);
}
