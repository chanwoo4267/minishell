/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_exception.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjung <sehjung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 17:41:49 by sehjung           #+#    #+#             */
/*   Updated: 2023/01/12 19:11:06 by sehjung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	str_moveup(char **str, int i)
{
	while (str[i])
	{
		str[i] = str[i + 1];
		i++;
	}
}

void	remove_special_char(char **str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] == ';' || str[i][j] == '\\' || str[i][j] == '&')
			{
				while (str[i][j])
				{
					str[i][j] = str[i][j + 1];
					j++;
				}
				j = 0;
				continue ;
			}
			j++;
		}
		if (!str[i][0])
			str_moveup(str, i);
		i++;
	}
}
