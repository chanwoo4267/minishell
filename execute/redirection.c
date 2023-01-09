/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwopa <chanwopa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 17:07:50 by chanwopa          #+#    #+#             */
/*   Updated: 2023/01/09 20:19:22 by chanwopa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FAIL 0
#define SUCCESS 1

typedef enum e_type
{
	COMMAND,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC,
}	t_type;

int	redirection(t_list	*redirection)
{
	t_token	*token;

	while (redirection)
	{
		token = (t_token *)redirection->content;
		if (token->type == REDIR_IN)
			redirect_input(token->content);
		else if (token->type == REDIR_OUT)
			redirect_output(token->content);
		else if (token->type == REDIR_HEREDOC)
			redirect_heredoc(token->content);
		else if (token->type == REDIR_APPEND)
			redirect_append(token->content);
		else
		{
			print_error();
			break ;
		}
		redirection = redirection->next;
	}
}

void	redirect_input(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		print_error();
	else if (fd != STDIN_FILENO)
	{
		if (dup2(fd, STDIN_FILENO) != STDIN_FILENO)
			print_error();
		close(fd);
	}
}

void	redirect_output(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		print_error();
	else if (fd != STDOUT_FILENO)
	{
		if (dup2(fd, STDOUT_FILENO) != STDOUT_FILENO)
			print_error();
		close(fd);
	}
}

void	redirect_append(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		print_error();
	else if (fd != STDOUT_FILENO)
	{
		if (dup2(fd, STDOUT_FILENO) != STDOUT_FILENO)
			print_error();
		close(fd);
	}
}

void	redirect_heredoc(char *delimiter)
{
	int		fd;
	char	*line;

	fd = open("/minishell/heredoc_temp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		print_error();
		return ;
	}
	line = get_next_line(STDIN_FILENO);
	while (line != NULL)
	{
		if (ft_strncmp(delimiter, line, ft_strlen(delimiter)) == 0
			&& line[ft_strlen(delimiter)] == '\n')
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	close(fd);
	redir_input("/minishell/heredoc_temp");
	unlink("/minishell/heredoc_temp");
}
