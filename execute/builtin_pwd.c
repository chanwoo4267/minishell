/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwopa <chanwopa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:06:26 by chanwopa          #+#    #+#             */
/*   Updated: 2023/01/20 19:12:16 by chanwopa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "execution_test.h"

void	builtin_pwd(t_list *list)
{
	char	**command;
	char	*pwd;

	command = list_to_strs(list);
	if (!command || command[1])
	{
		free_strs(command);
		error_return("builtin_pwd, invalid argument");
		return ;
	}
	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
	free(pwd);
	free_strs(command);
}
