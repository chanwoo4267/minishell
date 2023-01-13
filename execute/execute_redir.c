/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwopa <chanwopa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 17:07:50 by chanwopa          #+#    #+#             */
/*   Updated: 2023/01/14 03:04:15 by chanwopa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "execution_test.h"

/*
	REDIR_IN, REDIR_OUT 은 각각 0,1로 STDIN_FILENO, STDOUT_FILENO와 일치함 - 헤더참조
*/
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

/*
	heredoc에 대응하기 위한 임시파일을 생성하기 위한 경로를 결정한다.
	cat << a | cat << a 와 같은 piped-heredoc 에 대응하기 위해
	pipe 별로 fork() 및 execute_subshell 을 실행할 때
	각 fd에 맞는 cmd_idx를 인자로 넘겨준다. (pipe가 없다면 cmd_idx == 0)
	이를 바탕으로 파일 이름을 연다.
	단, 두 터미널에서 동시에 minishell을 실행하고 heredoc할경우 오류 발생
*/
char	*get_heredoc_filename(int *fd, int cmd_idx)
{
	char	*filename;
	char	*num;

	num = ft_itoa(cmd_idx);
	if (!num)
		print_error("get_heredoc_filename", "ft_itoa error");
	filename = ft_strjoin("heredoc_tmp", num);
	free(num);
	if (!filename)
		print_error("get_heredoc_filename", "ft_strjoin error");
	*fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*fd < 0)
	{
		free(filename);
		print_error("get_heredoc_filename", "open error");
	}
	return (filename);
}

void	redirect_heredoc(char *delimiter, int cmd_idx)
{
	int		fd;
	char	*line;
	char	*filename;

	filename = get_heredoc_filename(&fd, cmd_idx);
	if (!filename)
		print_error("redirect_heredoc", "filename error");
	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		print_message(line);
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

int	redirection(t_list	*redirection, int cmd_idx)
{
	t_token	*token;

	while (redirection)
	{
		token = (t_token *)redirection->content;
		if (token->type == REDIR_IN || token->type == REDIR_OUT || \
			token->type == REDIR_APPEND)
			redirect_file(token->content, token->type);
		else if (token->type == REDIR_HEREDOC)
			redirect_heredoc(token->content, cmd_idx);
		else
		{
			print_error("redirection", "token type error");
			break ;
		}
		redirection = redirection->next;
	}
	return (0);
}
