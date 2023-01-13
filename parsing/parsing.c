/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjung <sehjung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 17:46:51 by sehjung           #+#    #+#             */
/*   Updated: 2023/01/13 18:45:51 by sehjung          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

//#include "../minishell.h"
#include "parsing.h"

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
			j++;
		else
			ft_lstadd_back(&lst[j].command, ft_lstnew(new_token(str[i], COMMAND))); // 나누기
		i++;
	}
	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
	return (lst);
}

int	set_quoto(char c, int quote)
{
	if (c == '\'')
	{
		if (quote == 1)
			return (0);
		else if (quote == 2)
			return (2);
		else
			return (1);
	}
	else if (c == '\"')
	{
		if (quote == 2)
			return (0);
		else if (quote == 1)
			return (1);
		else
			return (2);
	}
}

void	check_quote(char *line)
{
	int	i;
	int	quote;
	int	pipe;
	char	*str;

	i = 0;
	quote = 0;
	str = ft_strdup("");
	while (line[i])
	{
		quote = set_quote(line[i], quote);
		if (quote == 0 && line[i] == '|')
		{
			if (pipe == 1)
				exit(1) // double pipe error
			
		}
		if (quote != 0 && line[i] == ' ')
			ft_strjoin(str, -1); // 공백을 -1로 넣고 나중에 치환하기
		else
		{
			ft_strjoin(str, line[i]);
			pipe = 0;
		}
		i++;
	}
	if (quote)
		exit(1) ; // single or double quote error
	return (str);
}

t_commandlist	*parsing(char *str)
{
	int		i;
	int		cnt;
	char	**split_str;
	t_commandlist *lst;

	i = 0;
	cnt = count_pipe(str);
	lst = ft_calloc(sizeof(t_commandlist) , cnt + 1);
	split_str = ft_split(str, ' ');
	remove_special_char(split_str);
	init_list(split_str, lst);
	return (lst);
}
