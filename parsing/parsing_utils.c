/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjung <sehjung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 19:02:14 by sehjung           #+#    #+#             */
/*   Updated: 2023/01/16 19:20:55 by sehjung          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

# include "parsing.h"

char	*ft_strjoin_char(char *s1, char s2)
{
	char	*ret;
	size_t	s1_len;

	if (!s1 && !s2)
		return (0);
	else if (!s1)
		return (ft_strdup(&s2));
	s1_len = ft_strlen(s1);
	ret = malloc(sizeof(char) * (s1_len + 2));
	if (!ret)
		return (0);
	ft_strlcpy(ret, s1, s1_len + 1);
	ft_strlcpy(ret + s1_len, &s2, 2);
	free(s1);
	return (ret);
}

t_token	*new_token(char *command, t_type type)
{
	t_token	*new_token;

	new_token = ft_calloc(sizeof(t_token), 1);
	new_token->content = ft_strdup(command);
	new_token->type = type;
	return (new_token);
}
