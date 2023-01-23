/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_dollar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjung <sehjung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 16:12:57 by sehjung           #+#    #+#             */
/*   Updated: 2023/01/23 21:06:28 by sehjung          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*envp_to_str(char *str, char **envp, int j)
{
	int		i;
	int		mystrlen;
	int		envlen;
	char	*temp;

	mystrlen = ft_strlen(str);
	envlen = ft_strlen(envp[j]) - mystrlen;
	temp = ft_substr(envp[j], mystrlen + 1, envlen - 1);
	return (temp);
}

t_list	*convert_envp(char *str, char **envp, t_type type)
{
	t_list	*temp;
	int		j;

	temp = ft_lstnew(new_token(envp_to_str(str, envp, j), type));
	return (NULL);
}

static void	ascii_change_qoute(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		str[i] = str[i + 1];
		i++;
	}
}

char	*dollar_split(char *str, char **envp)
{
	char	**split_str;
	char	*temp;
	int		i;
	int		j;
	
	i = 0;
	j = 0;
	split_str = ft_split(str, '$');
	if (str[0] != '$')
	{
		free(str);
		temp = ft_strdup(split_str[i]);
	}
	else
		free(str);
	if (!temp)
		temp = ft_strdup("");
	while (split_str[i])
	{
		j = 0;
		while(envp[j])
		{
			if (ft_strncmp(split_str[i], envp[j], ft_strlen(split_str[i])) == 0)
			{
				temp = ft_strjoin(temp, envp_to_str(split_str[i], envp, j));
				break;
			}
			j++;
		}
		i++;
	}
	return (temp);
}

int	find_dollar(char *str)
{
	int	i;

	i = 0;
	while(str)
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}