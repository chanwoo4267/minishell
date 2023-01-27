/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_dollar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjung <sehjung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 21:27:16 by sehjung           #+#    #+#             */
/*   Updated: 2023/01/27 17:44:07 by sehjung          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static t_dollar	*just_dollar(t_dollar *lst, char **envp, int i)
{
	if (ft_strlen(lst->str) < 1)
		return (lst);
	else if (lst->str[i] == '$'
		&& (lst->str[i + 1] == ' ' || lst->str[i + 1] == '\0'))
	{
		if (lst->d_temp != NULL)
			lst = convert_envp(lst, envp);
		if (lst->temp == NULL)
			lst->temp = ft_strdup("$");
		else
			lst->temp = ft_strjoin_char(lst->temp, '$');
		if (lst->str[i + 1] == ' ')
		{
			lst->str += 1;
			lst->check = 1;
		}
		else
			lst->check = 2;
		free(lst->d_temp);
		lst->d_temp = NULL;
		lst->dollar = 0;
	}
	return (lst);
}

static t_dollar	*exit_status(t_dollar *lst, char **envp)
{
	int	i;

	i = 0;
	lst->check = 0;
	if (ft_strlen(lst->str) < 1)
		return (lst);
	else if (lst->str[i] == '$' && lst->str[i + 1] == '?')
	{
		if (lst->d_temp != NULL)
			lst = convert_envp(lst, envp);
		if (lst->temp == NULL)
			lst->temp = ft_strdup(ft_itoa(g_status.global_exit_status));
		else
			lst->temp = ft_strjoin(lst->temp,
					ft_itoa(g_status.global_exit_status));
		free(lst->d_temp);
		lst->d_temp = NULL;
		lst->check = 1;
		lst->dollar = 0;
		lst->str += 2;
		return (lst);
	}
	return (lst);
}

static t_dollar	*end_dollar(char **envp, t_dollar *lst)
{
	lst = convert_envp(lst, envp);
	if (*lst->str == ' ')
	{
		lst->dollar = 0;
		lst->temp = ft_strjoin_char(lst->temp, *lst->str);
	}
	else
		lst->d_temp = ft_strjoin_char(lst->d_temp, *lst->str);
	lst->str++;
	return (lst);
}

static t_dollar	*circuit_str(t_dollar *lst, char **envp)
{
	while (*lst->str)
	{
		if (*lst->str == '$' || lst->dollar == 1)
		{
			lst = exit_status(lst, envp);
			lst = just_dollar(lst, envp, 0);
			if (lst->check == 1)
				continue ;
			else if (lst->check == 2)
				break ;
			if (lst->dollar == 1 && (*lst->str == ' ' || *lst->str == '$'))
			{
				lst = end_dollar(envp, lst);
				continue ;
			}
			lst->d_temp = ft_strjoin_char(lst->d_temp, *lst->str);
			lst->dollar = 1;
		}
		else if (lst->dollar == 0)
			lst->temp = ft_strjoin_char(lst->temp, *lst->str);
		lst->str++;
	}
	return (lst);
}

char	*convert_dollar(char *str, char **envp)
{
	t_dollar	*lst;
	char		*ret;

	lst = init_dollar(str);
	lst = circuit_str(lst, envp);
	if (lst->dollar == 1)
		lst = convert_envp(lst, envp);
	ret = free_dollar(lst, ret);
	free(lst);
	return (ret);
}
