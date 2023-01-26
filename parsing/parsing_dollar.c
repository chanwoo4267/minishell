/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_dollar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjung <sehjung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 16:12:57 by sehjung           #+#    #+#             */
/*   Updated: 2023/01/26 21:01:30 by sehjung          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
}

char	*exit_status(char *str, char *temp, char *d_temp,int *check)
{
	int	i;

	i = 0;
	if (ft_strlen(str) < 1)
		return (temp);
	else if (str[i] == '$' && str[i + 1] == '?')
	{
		if (temp == NULL)
			temp = ft_strdup(ft_itoa(g_status.global_exit_status));
		else
			temp = ft_strjoin(temp, ft_itoa(g_status.global_exit_status));
		free(d_temp);
		d_temp = NULL;
		*check = 1;
		return (temp);
	}
	return (temp);
}

char	*convert_dollar(char *str, char **envp, int dollar, int check)
{
	char	*temp;
	char	*d_temp;
	
	temp = NULL;
	d_temp = NULL;
	while (*str)
	{
		if (*str == '$' || dollar == 1)
		{
			temp = exit_status(str, temp, d_temp, &check);
			if (check == 1)
			{
				str += 2;
				check = 0;
				continue;
			}
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
	return (temp);
}
