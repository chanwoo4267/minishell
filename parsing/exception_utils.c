/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exception_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjung <sehjung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:39:27 by sehjung           #+#    #+#             */
/*   Updated: 2023/01/30 17:51:32 by sehjung          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	redirect_quote(char c)
{
	if (c == '<')
		return (-20);
	else if (c == '>')
		return (-21);
	else if (c == '|')
		return (-22);
	else
		return (0);
}

int	syntax_pipe(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line [i] == '|')
		{
			if (line[i + 1] == '>' || line[i + 1] == '<' || line[i + 1] == '|')
				return (1);
		}
		i++;
	}
	return (0);
}

int	syntax_redirect(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '>')
		{
			if (line[i + 1] == '<' || line[i + 1] == '|' || line[i + 1] == '\0')
				return (1);
			else if (line[i + 2] && (line[i + 2] == '<'
					|| line[i + 2] == '>' || line[i + 2] == '|'))
				return (1);
		}
		else if (line[i] == '<')
		{
			if (line[i + 1] == '>' || line[i + 1] == '|' || line[i + 1] == '\0')
				return (1);
			else if (line[i + 2] && (line[i + 2] == '<'
					|| line[i + 2] == '>' || line[i + 2] == '|'))
				return (1);
		}
		i++;
	}
	return (0);
}
