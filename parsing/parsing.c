/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjung <sehjung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 17:46:51 by sehjung           #+#    #+#             */
/*   Updated: 2023/01/26 21:38:47 by sehjung          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static t_commandlist	*init_parsing(char **str, t_commandlist *lst, char **envp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i][0] == '>')
			ft_lstadd_back(&lst[j].redirection, redirect_out(str, i++, envp));
		else if (str[i][0] == '<')
			ft_lstadd_back(&lst[j].redirection, redirect_in(str, i++, envp));
		else if (str[i][0] == '|')
			j++;
		else if (find_dollar(str[i]))
			ft_lstadd_back(&lst[j].command, ft_lstnew(new_token(convert_dollar(str[i], envp), COMMAND)));
		else
			ft_lstadd_back(&lst[j].command, ft_lstnew(new_token(str[i], COMMAND)));
		i++;
	}
	return (lst);
}

void	init_list(t_commandlist *lst, int cnt)
{
	int	i;

	i = 0;
	if (i < cnt)
	{
		lst[i].command = NULL;
		lst[i].redirection = NULL;
		i++;
	}
}

t_commandlist	*parsing(char *line, char **envp)
{
	char			*str;
	char			**split_str;
	t_commandlist	*lst;

	if (line[0] == '\0')
		return (NULL);
	str = exception_line(line);
	if (!str)
		return (NULL);
	split_str = ft_split(str, ' ');
	ascii_change(split_str);
	lst = ft_calloc((count_pipe(str) + 1), sizeof(t_commandlist));
	if (!lst)
		return (NULL);
	init_list(lst, count_pipe(str) + 1);
	init_parsing(split_str, lst, envp);
	//free_parsing_str(str, split_str); malloc된 문자열들 free, 다른 함수에서도 체크해야함
	return (lst);
}
