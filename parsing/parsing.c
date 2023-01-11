/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjung <sehjung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 17:46:51 by sehjung           #+#    #+#             */
/*   Updated: 2023/01/11 19:45:29 by sehjung          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

//#include "../minishell.h"
#include "parsing.h"

void	parse_command(char *str, t_list c_list)
{
	
}

void	parse_redirect(char *str, t_list *d_list)
{
	if (str[0] == '>')
	{
		if (str[1] == '>' && ft_strlen(str) == 2)
			ft_lstadd_back(&d_list, ft_lstnew(new_token(str, REDIR_APPEND)));
		else if (str[1] == '\0')
			ft_lstadd_back(&d_list, ft_lstnew(new_token(str, REDIR_OUT)));
	}
	else if (str[0] == '<')
	{
		if (str[1] == '<' && ft_strlen(str) == 2)
			ft_lstadd_back(&d_list, ft_lstnew(new_token(str, REDIR_HEREDOC)));
		else if (str[1] == '\0')
			ft_lstadd_back(&d_list, ft_lstnew(new_token(str, REDIR_IN)));
	}	
}

void	parsing(char *str, t_commandlist *lst)
{
	int		i;
	int		j;
	char	**split_str;

	i = 0;
	j = 0;
	split_str = ft_split(str, ' ');
	while (split_str[i])
	{
		if (split_str[i][0] == '>' || split_str[i][0] == '<')
			parse_redirect(split_str[i], lst[j].redirection);
		else if (split_str[i][0] == '|')
		{
			ft_lstadd_back(&lst[j].command, NULL);
			ft_lstadd_back(&lst[j].redirection, NULL);
			j++;
		}
		else
			ft_lstadd_back(&lst[j].command, ft_lstnew(new_token(split_str[i], COMMAND))); // 나누기
		i++;
	}
	i = 0;
	while (split_str[i])
		free(split_str[i++]);
	free(split_str);
	ft_lstadd_back(&lst[j].command, NULL);
	ft_lstadd_back(&lst[j].redirection, NULL);
}