/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwopa <chanwopa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 12:35:54 by chanwopa          #+#    #+#             */
/*   Updated: 2023/01/20 19:05:30 by chanwopa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "execution_test.h"

static int	echo_option(char *str)
{
	int	i;

	if (!str || ft_strlen(str) < 2)
		return (NO);
	if (str[0] != '-' || str[1] != 'n')
		return (NO);
	i = 2;
	while (str[i] != '\0')
	{
		if (str[i] != 'n')
			return (NO);
		i++;
	}
	return (YES);
}

static void	setup_echo_option(int *i, int *option, char **command)
{
	int	flag;

	*i = 1;
	*option = 0;
	flag = echo_option(command[*i]);
	while (flag)
	{
		(*i)++;
		*option = 1;
		flag = echo_option(command[*i]);
	}
}

void	builtin_echo(t_list *list)
{
	int		i;
	int		option;
	char	**command;

	g_status.global_exit_status = 0;
	command = list_to_strs(list);
	if (!command)
		error_return("builtin_echo, list_to_strs error");
	else
	{
		if (!command[1])
			printf("\n");
		else
		{
			setup_echo_option(&i, &option, command);
			while (command[i] != NULL && command[i + 1] != NULL)
				printf("%s ", command[i++]);
			if (command[i] != NULL)
				printf("%s", command[i]);
			if (option == 0)
				printf("\n");
		}
	}
	free_strs(command);
}
