/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwopa <chanwopa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 16:37:09 by chanwopa          #+#    #+#             */
/*   Updated: 2023/01/17 13:08:45 by chanwopa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "execution_test.h"

/*envp를 그대로 가져오면 free를 못하는데, 이러면 한번 변경한 pwd를 다시 변경할때 메모리 누수 발생*/
static void	change_pwd(char *new_cmd, t_info *info)
{
	int		i;
	char	*equal_loc;

	equal_loc = ft_strchr(new_cmd, '=');
	if (!equal_loc)
		print_error("change_pwd", "no eqaul symbol");
	i = 0;
	while (info->envp[i] != NULL)
	{
		if (ft_strncmp(new_cmd, info->envp[i], equal_loc - new_cmd) == 0)
		{
			//free(info->envp[i]);
			info->envp[i] = ft_strdup(new_cmd);
		}
		i++;
	}
}

static void	change_envp_pwd(char *old_cwd, t_info *info)
{
	char	*str;
	char	*new_pwd;

	str = ft_strjoin("OLDPWD=", old_cwd);
	change_pwd(str, info);
	free(str);
	str = getcwd(NULL, 0);
	new_pwd = ft_strjoin("PWD=", str);
	free(str);
	change_pwd(new_pwd, info);
	free(new_pwd);
}

void	builtin_cd(t_list *list, t_info *info)
{
	char	*old_cwd;
	char	**command;

	command = list_to_strs(list);
	if (!command)
		print_error("builtin_cd", "list_to_str error");
	if (!command[1])
		print_error("builtin_cd", "no_directory");
	else
	{
		old_cwd = getcwd(NULL, 0);
		if (chdir(command[1]) == -1)
			print_error("builtin_cd", "cannot cd to dir");
		else
			change_envp_pwd(old_cwd, info);
		free(old_cwd);
	}
}
