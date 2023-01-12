/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjung <sehjung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 19:02:14 by sehjung           #+#    #+#             */
/*   Updated: 2023/01/12 19:25:09 by sehjung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "parsing.h"

t_token	*new_token(char *command, t_type type)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
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
