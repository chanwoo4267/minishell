/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_dollar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjung <sehjung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 16:12:57 by sehjung           #+#    #+#             */
/*   Updated: 2023/01/26 00:05:50 by sehjung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	exit_status(char **split_str)
{
	int	i;
	int	j;
	char	*temp;
	char	*temp2;

	i = 0;
	j = 0;
	temp = NULL;
	while (split_str[i])
	{
		if (split_str[i][0] == '?')
		{
			temp = ft_strdup(ft_itoa(g_status.global_exit_status));
			temp = ft_strjoin(temp, &split_str[i][1]);
			temp2 = split_str[i];
			split_str[i] = temp;
			free(temp2);
			}
		i++;
	}
}

char	*convert_envp(char *d_temp, char *temp, char **envp)
{
	int	i;

	i = 0;
	d_temp++;
	while (envp[i])
	{
		if (ft_strncmp(d_temp, envp[i], ft_strlen(d_temp)) == 0 && envp[i][ft_strlen(d_temp)] == '=')
		{
			if (!temp)
				temp = ft_strdup(envp_to_str(d_temp, envp, i));
			else
				temp = ft_strjoin(temp, envp_to_str(d_temp, envp, i));
			break;
		}
		i++;
	}
	d_temp--;
	free(d_temp);
	d_temp = ft_strdup("");
	return (temp);
	//free(d_temp);
}

char	*convert_dollar(char *str, char **envp)
{
	int		dollar;
	char	*temp;
	char	*d_temp;

	dollar = 0;
	temp = NULL;
	d_temp = NULL;
	while (*str)
	{
		if (*str == '$' || dollar == 1)
		{
			if (dollar == 1 && (*str == ' ' || *str == '$'))
			{
				temp = convert_envp(d_temp, temp, envp);
				if (*str == ' ')
				{
					dollar = 0;
					temp = ft_strjoin_char(temp, *str);
				}
				else
					d_temp = ft_strjoin_char(d_temp, *str);
				str++;
				continue;
			}
			d_temp = ft_strjoin_char(d_temp, *str);
			dollar = 1;
		}
		else if (dollar == 0)
			temp = ft_strjoin_char(temp, *str);
		str++;
	}
	if (dollar == 1)
		temp = convert_envp(d_temp, temp, envp);
	if (!temp)
		return (ft_strdup(""));
	return (temp);
}
