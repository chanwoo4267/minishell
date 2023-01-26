/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_dollar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjung <sehjung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 21:27:16 by sehjung           #+#    #+#             */
/*   Updated: 2023/01/26 22:23:57 by sehjung          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_dollar	*init_dollar(void)
{
	t_dollar *lst;

	lst = malloc(sizeof(t_dollar));
	if (!lst)
		return (NULL);
	lst->dollar = 0;
	lst->check = 0;
	lst->temp = NULL;
	lst->d_temp = NULL;
	return (lst);
}

t_dollar	*convert_envp(t_dollar *lst, char **envp)
{
	int	i;

	i = 0;
	lst->d_temp++;
	while (envp[i])
	{
		if (ft_strncmp(lst->d_temp, envp[i], ft_strlen(lst->d_temp)) == 0 && envp[i][ft_strlen(lst->d_temp)] == '=')
		{
			if (!lst->temp)
				lst->temp = ft_strdup(envp_to_str(lst->d_temp, envp, i));
			else
				lst->temp = ft_strjoin(lst->temp, envp_to_str(lst->d_temp, envp, i));
			break;
		}
		i++;
	}
	lst->d_temp--;
	free(lst->d_temp);
	lst->d_temp = ft_strdup("");
	return (lst);
}

t_dollar	*exit_status(char *str, t_dollar *lst, char **envp)
{
	int	i;

	i = 0;
	if (ft_strlen(str) < 1)
		return (lst);
	else if (str[i] == '$' && str[i + 1] == '?')
	{
		if (lst->d_temp != NULL) // $LESS$?$LESS 들어오면 첫번째 환경변수가 안들어감
				lst = convert_envp(lst, envp);
		if (lst->temp == NULL)
			lst->temp = ft_strdup(ft_itoa(g_status.global_exit_status));
		else
			lst->temp = ft_strjoin(lst->temp, ft_itoa(g_status.global_exit_status));
		free(lst->d_temp);
		lst->d_temp = NULL;
		lst->check = 1;
		return (lst);
	}
	return (lst);
}

//t_dollar	*parsing_dollar

char	*convert_dollar(char *str, char **envp)
{
	t_dollar	*lst;

	lst = init_dollar();
	while (*str)
	{
		if (*str == '$' || lst->dollar == 1)
		{
			lst = exit_status(str, lst, envp);
			if (lst->check == 1)
			{
				str += 2;
				lst->check = 0;
				lst->dollar = 0;
				continue;
			}
			if (lst->dollar == 1 && (*str == ' ' || *str == '$'))
			{
				lst = convert_envp(lst, envp);
				if (*str == ' ')
				{
					lst->dollar = 0;
					lst->temp = ft_strjoin_char(lst->temp, *str);
				}
				else
					lst->d_temp = ft_strjoin_char(lst->d_temp, *str);
				str++;
				continue;
			}
			lst->d_temp = ft_strjoin_char(lst->d_temp, *str);
			lst->dollar = 1;
		}
		else if (lst->dollar == 0)
			lst->temp = ft_strjoin_char(lst->temp, *str);
		str++;
	}
	if (lst->dollar == 1)
		lst = convert_envp(lst, envp);
	return (lst->temp);
}