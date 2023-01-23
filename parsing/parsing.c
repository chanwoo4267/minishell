/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjung <sehjung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 17:46:51 by sehjung           #+#    #+#             */
/*   Updated: 2023/01/23 21:09:34 by sehjung          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static t_commandlist	*init_list(char **str, t_commandlist *lst, char **envp)
{
	int	i;
	int	j;
	int	d;

	i = 0;
	j = 0;
	while (str[i])
	{
		d = find_dollar(str[i + 1]);
		if (str[i][0] == '>')
			ft_lstadd_back(&lst[j].redirection, redirect_out(str, i++, envp, d));
		else if (str[i][0] == '<')
			ft_lstadd_back(&lst[j].redirection, redirect_in(str, i++, envp, d));
		else if (str[i][0] == '|')
			j++;
		else
			ft_lstadd_back(&lst[j].command, ft_lstnew(new_token(str[i], COMMAND)));
		i++;
	}
	return (lst);
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
	lst = malloc(sizeof(t_commandlist) * (count_pipe(str) + 1));
	if (!lst)
		return (NULL);
	init_list(split_str, lst, envp);
	//free_parsing_str(str, split_str);
	return (lst);
}
