/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwopa <chanwopa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 17:07:50 by chanwopa          #+#    #+#             */
/*   Updated: 2023/01/26 15:07:02 by chanwopa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redirect_file(char *filename, t_type type)
{
	int	fd;
	int	standard_fd;

	fd = -1;
	standard_fd = type;
	if (type == REDIR_IN)
		fd = open(filename, O_RDONLY);
	else if (type == REDIR_OUT)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == REDIR_APPEND)
	{
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		standard_fd = STDOUT_FILENO;
	}
	if (fd < 0)
		print_error(filename, NULL, NULL, YES);
	else if (fd != standard_fd)
	{
		if (dup2(fd, standard_fd) != standard_fd)
			system_error("redirect_file", "dup2 error", 1);
		close(fd);
	}
}

void	redirection(t_list	*redirection)
{
	t_token	*token;
	t_list	*list;

	list = redirection;
	while (list)
	{
		token = (t_token *)list->content;
		if (token->type == REDIR_IN || token->type == REDIR_OUT || \
			token->type == REDIR_APPEND)
			redirect_file(token->content, token->type);
		else
			system_error("invalid token type ", token->content, 1);
		list = list->next;
	}
}
