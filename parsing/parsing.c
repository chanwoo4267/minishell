/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjung <sehjung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 17:46:51 by sehjung           #+#    #+#             */
/*   Updated: 2023/01/15 18:13:07 by sehjung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			ft_lstadd_back(&lst[j].command, ft_lstnew(new_token(str[i], COMMAND))); // $ 환경변수 치환하기
		i++;
	}
	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
	return (lst);
}

t_commandlist	*parsing(char *line)
{
	char	*str;
	char	**split_str;
	t_commandlist *lst;

	str = exception_line(line);
	printf("%s\n", str);
	lst = ft_calloc(sizeof(t_commandlist) , 10 + 1); // need cnt
	split_str = ft_split(str, ' ');
	// -10 -> 공백으로 치환하기
	init_list(split_str, lst);
	return (lst);
}
