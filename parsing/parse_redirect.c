/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjung <sehjung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 20:12:35 by sehjung           #+#    #+#             */
/*   Updated: 2023/01/26 19:31:53 by sehjung          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_list	*redirect_in(char **str, int i, char **envp)
{
	t_list	*temp;
	int		d;

	temp = NULL;
	if (str[i + 1] == NULL)
		return (NULL);
	d = find_dollar(str[i + 1]);
	if (str[i][0] == '<')
	{
		if (str[i][1] == '<' && ft_strlen(str[i]) == 2)
				temp = ft_lstnew(new_token(str[++i], REDIR_HEREDOC));
		else if (str[i][1] == '\0')
		{
			if (d)
				temp = ft_lstnew(new_token(convert_dollar(str[++i], envp, 0, 0), REDIR_IN));
			else
				temp = ft_lstnew(new_token(str[++i], REDIR_IN));
		}
		else
			return (NULL);
	}
	return (temp);
}

t_list	*redirect_out(char **str, int i, char **envp)
{
	t_list	*temp;
	int		d;

	temp = NULL;
	if (str[i + 1] == NULL)
		return (NULL);
	d = find_dollar(str[i + 1]);
	if (str[i][0] == '>')
	{
		if (str[i][1] == '>' && ft_strlen(str[i]) == 2)
		{
			if (d)
				temp = ft_lstnew(new_token(convert_dollar(str[++i], envp, 0, 0), REDIR_APPEND));
			else
				temp = ft_lstnew(new_token(str[++i], REDIR_APPEND));
		}
		else if (str[i][1] == '\0')
		{
			if (d)
				temp = ft_lstnew(new_token(convert_dollar(str[++i], envp, 0, 0), REDIR_OUT));
			else
				temp = ft_lstnew(new_token(str[++i], REDIR_OUT));
		}
		else
			return (NULL);
	}
	return (temp);
}
