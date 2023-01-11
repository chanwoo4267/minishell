/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjung <sehjung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 17:46:51 by sehjung           #+#    #+#             */
/*   Updated: 2023/01/11 17:49:51 by sehjung          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parsing.h"

t_token	*new_token(char *command, t_type type)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	new_token->content = ft_strdup(command);
	new_token->type = type;
	return (new_token);
}

t_commandlist	*parsing(char *str, t_commandlist *lst)
{
	int		i;
	int		j;
	char	**d_str;

	i = 0;
	j = 0;
	d_str = ft_split(str, ' ');

	while (d_str[i])
	{
		if (d_str[i][0] == '>')
		{
			if (d_str[i][1] == '>')
				ft_lstadd_back(&lst[j].redirection, ft_lstnew(new_token(d_str[++i], REDIR_APPEND)));
			else
				ft_lstadd_back(&lst[j].redirection, ft_lstnew(new_token(d_str[++i], REDIR_OUT)));
		}
		else if (d_str[i][0] == '<')
		{
			if (d_str[i][1] == '<')
				ft_lstadd_back(&lst[j].redirection, ft_lstnew(new_token(d_str[++i], REDIR_HEREDOC)));
			else
				ft_lstadd_back(&lst[j].redirection, ft_lstnew(new_token(d_str[++i], REDIR_IN)));
		}
		else if (d_str[i][0] == '|')
		{
			ft_lstadd_back(&lst[j].command, NULL);
			ft_lstadd_back(&lst[j].redirection, NULL);
			j++;
		}
		else
			ft_lstadd_back(&lst[j].command, ft_lstnew(new_token(d_str[i], COMMAND)));
		i++;
	}
	free(d_str);
	ft_lstadd_back(&lst[j].command, NULL);
	ft_lstadd_back(&lst[j].redirection, NULL);
	return (lst);
}