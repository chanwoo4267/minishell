/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwopa <chanwopa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 20:38:29 by chanwopa          #+#    #+#             */
/*   Updated: 2023/01/21 15:41:19 by chanwopa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_error(char *location, char *message)
{
	write(2, "Error in : ", 11);
	write(2, location, ft_strlen(location));
	write(2, "\nMsg: ", 6);
	write(2, message, ft_strlen(message));
	exit(1);
}

void	error_return(char *message, int error_code)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (message)
		ft_putendl_fd(message, STDERR_FILENO);
	g_status.global_exit_status = error_code;
}

void	error_exit(char *message, int error_code)
{
	ft_putstr_fd("minishell: ", 2);
	if (message)
		ft_putendl_fd(message, 2);
	exit(error_code);
}

void	print_message(char *message)
{
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
}

int	get_commands_count(t_commandlist *commandlist)
{
	int	count;

	count = 0;
	while (commandlist[count].command != NULL)
		count++;
	return (count);
}

char	**list_to_strs(t_list *command)
{
	t_list	*ptr;
	char	**strs;
	int		count;
	int		i;

	count = 0;
	ptr = command;
	while (ptr)
	{
		count++;
		ptr = ptr->next;
	}
	strs = malloc(sizeof(char *) * (count + 1));
	if (!strs)
		return (NULL);
	i = -1;
	ptr = command;
	while (++i < count)
	{
		strs[i] = ((t_token *)ptr->content)->content;
		ptr = ptr->next;
	}
	strs[i] = NULL;
	return (strs);
}

void	free_strs(char **strs)
{
	int	i;

	if (strs)
	{
		i = 0;
		while (strs[i])
		{
			free(strs[i]);
			i++;
		}
		free(strs);
	}
}
