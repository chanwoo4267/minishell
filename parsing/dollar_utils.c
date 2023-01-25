/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjung <sehjung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 23:41:26 by sehjung           #+#    #+#             */
/*   Updated: 2023/01/25 23:43:16 by sehjung          ###   ########.fr       */
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

int	find_dollar(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}
