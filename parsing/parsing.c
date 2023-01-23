/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjung <sehjung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 17:46:51 by sehjung           #+#    #+#             */
/*   Updated: 2023/01/23 16:14:10 by sehjung          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static t_commandlist	*init_list(char **str, t_commandlist *lst, char **envp)
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
		else if (str[i][0] == -11 && str[i][1] == '$')
			exit(1);//맨앞 -11 삭제
		else if (str[i][0] == '$')
		{
			if (str[i][1] == '?')
				ft_lstadd_back(&lst[j].command, ft_lstnew(new_token(ft_itoa(g_status.global_exit_status), DOLLAR_SIGN)));
			else
				ft_lstadd_back(&lst[j].command, convert_envp(str[i], envp, COMMAND));
		}
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
	free_parsing_str(str, split_str);
	return (lst);
}
