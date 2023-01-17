/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwopa <chanwopa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 12:35:54 by chanwopa          #+#    #+#             */
/*   Updated: 2023/01/17 13:09:03 by chanwopa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "execution_test.h"

void	builtin_echo(t_list *list, t_info *info)
{
	int		i;
	char	**command;

	command = list_to_strs(list);
	if (!command)
		print_error("builtin_echo", "list_to_strs error");
	g_status.global_exit_status = 0;
	if (!command[1])
	{
		printf("\n");
		return ;
	}
	if (ft_strncmp(command[1], "-n", ft_strlen(command[1])) == 0)
		i = 2;
	else
		i = 1;
	while (command[i] != NULL && command[i + 1] != NULL)
	{
		printf("%s ", command[i]);
		i++;
	}
	if (command[i] != NULL)
		printf("%s", command[i]);
	if (ft_strncmp(command[1], "-n", ft_strlen(command[1])) == 0)
		printf("\n");
}
