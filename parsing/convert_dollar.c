/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_dollar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjung <sehjung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 21:27:16 by sehjung           #+#    #+#             */
/*   Updated: 2023/01/27 15:59:32 by sehjung          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_dollar	*init_dollar(char *str)
{
	t_dollar *lst;

	lst = malloc(sizeof(t_dollar));
	if (!lst)
		return (NULL);
	lst->dollar = 0;
	lst->check = 0;
	lst->str = str;
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

t_dollar	*just_dollar(t_dollar *lst, char **envp)
{
	int	i;

	i = 0;
	if (ft_strlen(lst->str) < 1)
		return (lst);
	else if (lst->str[i] == '$' && (lst->str[i + 1] == ' ' || lst->str[i + 1] == '\0'))
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

t_dollar	*exit_status(t_dollar *lst, char **envp)
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
			lst->temp = ft_strjoin(lst->temp, ft_itoa(g_status.global_exit_status));
		free(lst->d_temp);
		lst->d_temp = NULL;
		lst->check = 1;
		lst->dollar = 0;
		lst->str += 2;
		return (lst);
	}
	return (lst);
}

t_dollar	*end_dollar(char **envp, t_dollar *lst)
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

char	*convert_dollar(char *str, char **envp)
{
	t_dollar	*lst;

	lst = init_dollar(str);
	while (*lst->str)
	{
		if (*lst->str == '$' || lst->dollar == 1)
		{
			lst = exit_status(lst, envp);
			lst = just_dollar(lst, envp);
			if (lst->check == 1)
				continue;
			else if (lst->check == 2)
				break;
			if (lst->dollar == 1 && (*lst->str == ' ' || *lst->str == '$'))
			{
				lst = end_dollar(envp, lst);
				continue;
			}
			lst->d_temp = ft_strjoin_char(lst->d_temp, *lst->str);
			lst->dollar = 1;
		}
		else if (lst->dollar == 0)
			lst->temp = ft_strjoin_char(lst->temp, *lst->str);
		lst->str++;
	}
	if (lst->dollar == 1)
		lst = convert_envp(lst, envp);
	return (lst->temp);
}
