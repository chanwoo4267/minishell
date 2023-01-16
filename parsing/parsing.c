/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjung <sehjung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 17:46:51 by sehjung           #+#    #+#             */
/*   Updated: 2023/01/16 20:30:34 by sehjung          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	parse_redirect(char **str, t_commandlist *lst, int i, int j)
{
	if (str[i][0] == '>')
	{
		if (str[i][1] == '>' && ft_strlen(str[i]) == 2)
			ft_lstadd_back(&lst[j].redirection, ft_lstnew(new_token(str[++i], REDIR_APPEND)));
		else if (str[i][1] == '\0')
			ft_lstadd_back(&lst[j].redirection, ft_lstnew(new_token(str[++i], REDIR_OUT)));
	}
	else if (str[i][0] == '<')
	{
		if (str[i][1] == '<' && ft_strlen(str[i]) == 2)
			ft_lstadd_back(&lst[j].redirection, ft_lstnew(new_token(str[++i], REDIR_HEREDOC)));
		else if (str[i][1] == '\0')
			ft_lstadd_back(&lst[j].redirection, ft_lstnew(new_token(str[++i], REDIR_IN)));
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
			parse_redirect(str, lst, i++, j);
		else if (str[i][0] == '|')
			j++;
		else
			ft_lstadd_back(&lst[j].command, ft_lstnew(new_token(str[i], COMMAND))); // $ 환경변수 치환하기
		if (str[i])
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
	printf("%s\n", str); //test
	split_str = ft_split(str, ' ');
	ascii_change(split_str);
	lst = ft_calloc(sizeof(t_commandlist) , 10 + 1); // need cnt
	init_list(split_str, lst);
	return (lst);
}
