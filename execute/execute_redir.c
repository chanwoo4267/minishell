/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwopa <chanwopa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 17:07:50 by chanwopa          #+#    #+#             */
/*   Updated: 2023/01/23 06:26:08 by chanwopa         ###   ########seoul.kr  */
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
			system_error("invalid token type", token->content, 1);
		list = list->next;
	}
}

char	*get_heredoc_filename(int *fd)
{
	char	*filename;
	char	*num;
	int		i;

	i = 0;
	while (++i)
	{
		num = ft_itoa(i);
		filename = ft_strjoin(".heredoc_tmp", num);
		if (num)
			free(num);
		if (!filename)
			system_error("get_heredoc_filename", "malloc error", 1);
		if (access(filename, F_OK) != 0)
		{
			*fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (*fd >= 0)
				return (filename);
		}
		free(filename);
	}
	return (NULL);
}

void	change_heredoc_to_redirin(t_token *token)
{
	int		fd;
	char	*line;
	char	*filename;
	char	*delimiter;

	delimiter = token->content;
	filename = get_heredoc_filename(&fd);
	line = readline(NULL);
	while (line)
	{
		if (ft_strncmp(delimiter, line, ft_strlen(delimiter)) == 0 && \
			ft_strncmp(delimiter, line, ft_strlen(line)) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = readline(NULL);
	}
	free(token->content); /* 안전한지 확인 필요 */
	token->content = filename;
	token->type = REDIR_IN;
	close(fd);
}

void	redirect_heredoc(t_commandlist *commandlist, int cmd_count)
{
	int		i;
	t_list	*lst;
	t_token	*token;

	i = -1;
	while (++i < cmd_count)
	{
		lst = commandlist[i].redirection;
		while (lst)
		{
			token = (t_token *)lst->content;
			if (token->type == REDIR_HEREDOC)
				change_heredoc_to_redirin(token);
			lst = lst->next;
		}
	}
}
