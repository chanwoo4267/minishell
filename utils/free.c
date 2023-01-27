/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwopa <chanwopa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 20:18:23 by chanwopa          #+#    #+#             */
/*   Updated: 2023/01/27 19:44:51 by chanwopa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	free_lists(t_list *list)
{
	t_list	*ptr;
	t_token	*token;

	ptr = list;
	while (ptr)
	{
		token = ptr->content;
		ptr = ptr->next;
		if (token)
		{
			if (token->content)
				free(token->content);
			free(token);
		}
	}
}

void	free_commands(t_commandlist *commandlist)
{
	int	i;

	if (!commandlist)
		return ;
	i = 0;
	while (commandlist[i].command || commandlist[i].redirection)
	{
		if (commandlist[i].command)
			free_lists(commandlist[i].command);
		if (commandlist[i].redirection)
			free_lists(commandlist[i].redirection);
		i++;
	}
	free(commandlist);
}
