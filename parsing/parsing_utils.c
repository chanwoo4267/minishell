/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjung <sehjung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 19:02:14 by sehjung           #+#    #+#             */
/*   Updated: 2023/01/11 19:02:27 by sehjung          ###   ########seoul.kr  */
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
