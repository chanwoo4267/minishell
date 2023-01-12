/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjung <sehjung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 17:46:51 by sehjung           #+#    #+#             */
/*   Updated: 2023/01/12 19:24:57 by sehjung          ###   ########.fr       */
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

t_commandlist	*init_list(char **str, t_commandlist *lst)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i][0] == '>' || str[i][0] == '<')
			parse_redirect(str[i], lst[j].redirection);
		else if (str[i][0] == '|')
		{
			ft_lstadd_back(&lst[j].command, NULL);
			ft_lstadd_back(&lst[j].redirection, NULL);
			j++;
		}
		else
			ft_lstadd_back(&lst[j].command, ft_lstnew(new_token(str[i], COMMAND))); // 나누기
		i++;
	}
	while (str[i])
		free(str[i++]);
	free(str);
	ft_lstadd_back(&lst[j].command, NULL);
	ft_lstadd_back(&lst[j].redirection, NULL);
	return (lst);
}

t_commandlist	*parsing(char *str)
{
	int		i;
	int		cnt;
	char	**split_str;
	t_commandlist *lst;

	i = 0;
	cnt = count_pipe(str);
	lst = malloc(sizeof(t_commandlist *) * cnt + 1);
	split_str = ft_split(str, ' ');
	remove_special_char(split_str);
	init_list(split_str, lst);
	return (lst);
}
