/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwopa <chanwopa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 18:40:11 by chanwopa          #+#    #+#             */
/*   Updated: 2023/01/12 19:16:26 by chanwopa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "execution_test.h"

int	execute_command(t_list *command, t_info *info)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		print_error();
	else if (pid == 0)
	{
		info->issubshell = YES;
		execute_command_subshell(command, info->envp);
	}
	if (waitpid(pid, &status, 0) < 0)
		print_error();
	if (WIFEXITED(status)) /* 자식 프로세스가 정상적으로 종료됬다면, 자식 프로세스의 종료 코드를 저장 */
		g_status.global_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status)) /* 자식 프로세스가 비정상적으로 종료됬다면, 시그널 번호를 저장 */
		g_status.global_exit_status = WTERMSIG(status);
	else
		g_status.global_exit_status = EXIT_FAILURE;
	return (0);
}

char	*get_env_path(char **env)
{
	char	*path;

	while (*env && ft_strncmp(*env, "PATH=", 5) != 0)
		env++;
	if (*env == NULL)
		path = NULL;
	else
	{
		path = ft_strchr(*env, '=') + 1;
		if (*path == '\0')
			path = NULL;
	}
	return (path);
}

static char	*merge_command_path(char *command, char *path, size_t path_len)
{
	size_t	command_len;
	char	*cmd;

	command_len = ft_strlen(command);
	cmd = malloc(sizeof(char) * (command_len + path_len + 2));
	if (cmd == NULL)
		print_error();
	ft_memcpy(cmd, path, path_len);
	cmd[path_len] = '/';
	ft_memcpy(cmd + path_len + 1, command, command_len);
	cmd[path_len + command_len + 1] = '\0';
	return (cmd);
}

char	*get_absolute_cmd(char *command, char *path)
{
	size_t	path_len;
	char	*ptr;
	char	*cmd;

	while (*path)
	{
		ptr = path;
		while (*ptr && *ptr != ':')
			ptr++;
		if (ptr == path)
		{
			path_len = 1;
			path = ".";
		}
		else
			path_len = ptr - path;
		cmd = merge_command_path(command, path, path_len);
		if (access(cmd, X_OK) == 0)
			return (cmd);
		free(cmd);
		path = ptr + 1;
	}
	return (NULL);
}


int	execute_command_subshell(t_list *command, char **envp)
{
	char	**cmd;
	char	**env;
	char	*path;
	char	*absolute_cmd;

	cmd = list_to_strs(command);
	env = envp;
	if (ft_strchr(cmd[0], '/'))
		execute_given_path(cmd, envp);
	path = get_env_path(env);
	/* test
	write(2, "path : ", 7);
	write(2, path, ft_strlen(path));
	write(2, "\n", 1); */
	if (path == NULL)
		print_error();
	absolute_cmd = get_absolute_cmd(cmd[0], path);
	if (!absolute_cmd)
		print_error();
	if (execve(absolute_cmd, cmd, envp) < 0)
		print_error();
	return (0);
}

int	execute_given_path(char **cmd, char **envp)
{
	char	*command;

	command = cmd[0];
	if (execve(command, cmd, envp) < 0)
		print_error();
	return (0);
}
