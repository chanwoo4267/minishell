/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exception_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjung <sehjung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:39:27 by sehjung           #+#    #+#             */
/*   Updated: 2023/02/01 00:12:56 by sehjung          ###   ########.fr       */
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

int	syntax_pipe(char *str)
{
	int	i;

	i = 0;
	if (str[0] == ' ' && str[1] == '|')
		return (1);
	while (str[i])
	{
		if (str[i] == '|')
		{
			if (!str[i + 2])
				return (1);
			else if (str[i + 2] == '>' || str[i + 2] == '<'
				|| str[i + 2] == '|')
				return (1);
		}
		i++;
	}
	return (0);
}

int	syntax_redirect2(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '>')
		{
			if (!str[i + 2])
				return (1);
			else if (str[i + 2] == '>' || str[i + 2] == '<'
				|| str[i + 2] == '|')
				return (1);
		}
		if (str[i] == '<')
		{
			if (!str[i + 2])
				return (1);
			else if (str[i + 2] == '>' || str[i + 2] == '<'
				|| str[i + 2] == '|')
				return (1);
		}
		i++;
	}
	return (0);
}

int	syntax_redirect(char *line)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	if (line[0] == '|')
		return (1);
	while (line[i])
	{
		quote = set_quote(line[i], quote);
		if (line[i] == '>' && quote == 0)
		{
			if (line[i + 1] == '<' || line[i + 1] == '|' || line[i + 1] == '\0')
				return (1);
		}
		else if (line[i] == '<' && quote == 0)
		{
			if (line[i + 1] == '>' || line[i + 1] == '|' || line[i + 1] == '\0')
				return (1);
		}
		i++;
	}
	return (0);
}
