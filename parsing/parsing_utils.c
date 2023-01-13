/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjung <sehjung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 19:02:14 by sehjung           #+#    #+#             */
/*   Updated: 2023/01/13 17:45:38 by sehjung          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

# include "parsing.h"

void	del_token(void *token)
{
	
}

void	free_list(t_commandlist *lst)
{
	
}

t_token	*new_token(char *command, t_type type)
{
	t_token	*new_token;

	new_token = ft_calloc(sizeof(t_token), 1);
	new_token->content = ft_strdup(command);
	new_token->type = type;
	return (new_token);
}

int	count_pipe(char *str)
{
	int	i;
	int cnt;

	i = 0;
	cnt = 0;
	while (str[i])
	{
		if (str[i] == '|')
			cnt++;
		i++;
	}
	return (cnt);
}
