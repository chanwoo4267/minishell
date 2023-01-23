/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_dollar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjung <sehjung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 16:12:57 by sehjung           #+#    #+#             */
/*   Updated: 2023/01/23 16:23:15 by sehjung          ###   ########seoul.kr  */
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
	char	*trim;
	t_list	*temp;
	int		j;

	j = 0;
	trim = ft_strtrim(str, "$");
	while (envp[j])
	{
		if (ft_strncmp(trim, envp[j], ft_strlen(trim)) == 0)
		{
			temp = ft_lstnew(new_token(envp_to_str(trim, envp, j), type));
			free(trim);
			return (temp);
		}
		j++;
	}
	return (NULL);
}

void	parsing_dollar(char *str, t_list *lst, char **envp)
{
	if (str[0] == -11 && str[1] == '$')
		exit(1);
	else if (str[0] == '$')
	{
		if (str[1] == '?')
			ft_lstadd_back(&lst, ft_lstnew(new_token(ft_itoa(g_status.global_exit_status), DOLLAR_SIGN)));
		else
			ft_lstadd_back(&lst, convert_envp(str, envp, COMMAND));
	}
}