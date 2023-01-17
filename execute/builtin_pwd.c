/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwopa <chanwopa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:06:26 by chanwopa          #+#    #+#             */
/*   Updated: 2023/01/17 13:10:32 by chanwopa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "execution_test.h"

void	builtin_pwd(t_list *list, t_info *info)
{
	char	**command;
	char	*pwd;

	command = list_to_strs(list);
	if (!command)
		print_error("builtin_pwd", "list_to_strs error");
	if (!command[1])
	{
		print_error("builtin_pwd", "no argument with pwd");
		return ;
	}
	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
	free(pwd);
}
