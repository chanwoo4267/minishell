/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ascii_change.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjung <sehjung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 19:21:05 by sehjung           #+#    #+#             */
/*   Updated: 2023/01/23 16:05:39 by sehjung          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	double_quote(char *str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\"')
		{
			j = i;
			while (str[j])
			{
				str[j] = str[j + 1];
				j++;
			}
			i--;
		}
		i++;
	}
}

static void	single_quote(char *str)
{
	int	i;
	int	j;

	i = 0;
	if (str[1] == '$')
		str[0] = -11;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			j = i;
			while (str[j])
			{
				str[j] = str[j + 1];
				j++;
			}
			i--;
		}
		i++;
	}
}

static void	del_quote(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i][0] == '\'')
			single_quote(str[i]);
		else if (str[i][0] == '\"')
			double_quote(str[i]);
		i++;
	}
}

void	ascii_change(char **str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] == -10)
				str[i][j] = ' ';
			j++;
		}
		i++;
	}
	del_quote(str);
}
