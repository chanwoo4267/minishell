/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwopa <chanwopa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 17:07:50 by chanwopa          #+#    #+#             */
/*   Updated: 2023/01/13 19:55:21 by chanwopa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "execution_test.h"

/* REDIR_IN, REDIR_OUT 은 각각 0,1로 STDIN_FILENO, STDOUT_FILENO와 일치함 */
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
		print_error("redirect_file", "open error");
	else if (fd != standard_fd)
	{
		if (dup2(fd, standard_fd) != standard_fd)
			print_error("redirect_file", "dup2 error");
		close(fd);
	}
}

int	redirection(t_list	*redirection)
{
	t_token	*token;

	while (redirection)
	{
		token = (t_token *)redirection->content;
		printf("%d\n", token->type);
		if (token->type == REDIR_IN || token->type == REDIR_OUT || \
			token->type == REDIR_APPEND)
			redirect_file(token->content, token->type);
		else if (token->type == REDIR_HEREDOC)
			redirect_heredoc(token->content);
		else
		{
			print_error("redirection", "token type error");
			break ;
		}
		redirection = redirection->next;
	}
	return (0);
}

char	*get_heredoc_filename(int *fd)
{
	char	*filename;
	char	*num;
	int		i;

	i = -1;
	while (++i < OPEN_TRY_MAX)
	{
		num = ft_itoa(i);
		if (!num)
			print_error("get_heredoc_filename", "malloc error");
		filename = ft_strjoin("heredoc_tmp", num);
		if (!filename)
			print_error("get_heredoc_filename", "malloc error");
		*fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		free(num);
		if (*fd >= 0)
			return (filename);
		free(filename);
	}
	print_error("get_heredoc_filename", "open error");
	return (NULL);
}

void	redirect_heredoc(char *delimiter)
{
	int		fd;
	char	*line;
	char	*filename;

	filename = get_heredoc_filename(&fd);
	if (!filename)
		print_error("redirect_heredoc", "filename error");
	line = get_next_line(STDIN_FILENO);
	while (line)
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
	redirect_file(filename, REDIR_IN);
	unlink(filename);
	free(filename);
}
