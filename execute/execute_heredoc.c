/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwopa <chanwopa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 15:06:19 by chanwopa          #+#    #+#             */
/*   Updated: 2023/01/26 16:52:32 by chanwopa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_heredoc_filename(int *fd)
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

void	heredoc_to_redirin(t_token *token, int *fds, int index)
{
	char	*filename;

	filename = get_heredoc_filename(&fds[index]);
	if (!filename)
		system_error("heredoc_to_redirin", "heredoc tmp exceeded maximum", 1);
	free(token->content);
	token->content = filename;
	token->type = REDIR_IN;
}

int	fork_redirection(int heredoc_count, int *fds, char **delims)
{
	int		i;
	int		pid;
	int		status;
	char	*line;

	i = -1;
	while (++i < heredoc_count)
	{
		pid = fork();
		if (pid < 0)
			system_error("fork_redirection", "fork error", 1);
		else if (pid == 0)
		{
			sig_fork(HEREDOC);
			line = readline("> ");
			while (line)
			{
				if (ft_strncmp(delims[i], line, ft_strlen(delims[i])) == 0 && \
					ft_strncmp(delims[i], line, ft_strlen(line)) == 0)
				{
					free(line);
					break ;
				}
				write(fds[i], line, ft_strlen(line));
				write(fds[i], "\n", 1);
				free(line);
				line = readline("> ");
			}
			exit(0);
		}
		if (waitpid(pid, &status, 0) < 0)
			system_error("fork_redirection", "waitpid error", 1);
		if (WIFEXITED(status))
			g_status.global_exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			g_status.global_exit_status = WTERMSIG(status);
			return (FAIL);
		}
		else
			system_error("fork_redirection", "exit failure error", 1);
	}
	return (SUCCESS);
}

int	change_token_and_open(t_commandlist *commandlist, int cmd_count, \
							int heredoc_count, char **delims)
{
	int		*fds;
	int		i;
	int		idx;
	t_list	*lst;

	fds = malloc(sizeof(int) * heredoc_count);
	delims = malloc(sizeof(char *) * heredoc_count);
	if (!fds || !delims)
		system_error("change_token_and_open", "malloc error", 1);
	i = -1;
	idx = 0;
	while (++i < cmd_count)
	{
		lst = commandlist[i].redirection;
		while (lst)
		{
			if (((t_token *)lst->content)->type == REDIR_HEREDOC)
			{
				delims[idx] = ft_strdup(((t_token *)lst->content)->content);
				heredoc_to_redirin((t_token *)lst->content, fds, idx++);
			}
			lst = lst->next;
		}
	}
	return (fork_redirection(heredoc_count, fds, delims));
}

int	redirect_heredoc(t_commandlist *commandlist, int cmd_count)
{
	int		i;
	int		count;
	t_list	*lst;
	char	**delims;

	count = 0;
	i = -1;
	while (++i < cmd_count)
	{
		lst = commandlist[i].redirection;
		while (lst)
		{
			if (((t_token *)lst->content)->type == REDIR_HEREDOC)
				count++;
			lst = lst->next;
		}
	}
	return (change_token_and_open(commandlist, cmd_count, count, delims));
}
