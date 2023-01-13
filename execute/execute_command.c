/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwopa <chanwopa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 18:40:11 by chanwopa          #+#    #+#             */
/*   Updated: 2023/01/13 18:48:51 by chanwopa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "execution_test.h"

static char	*get_env_path(char **env)
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
		print_error("merge_command_path", "malloc error");
	ft_memcpy(cmd, path, path_len);
	cmd[path_len] = '/';
	ft_memcpy(cmd + path_len + 1, command, command_len);
	cmd[path_len + command_len + 1] = '\0';
	return (cmd);
}

static char	*get_cmd_from_path(char *command, char *path)
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

int	execute_command(t_list *command, t_info *info)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		print_error("execute_command", "fork error");
	else if (pid == 0)
	{
		info->issubshell = YES;
		execute_command_subshell(command, info->envp);
	}
	if (waitpid(pid, &status, 0) < 0)
		print_error("execute_command", "waitpid error");
	/* 자식 프로세스가 정상적으로 종료됬다면, 자식 프로세스의 종료 코드를 저장 */
	if (WIFEXITED(status))
		g_status.global_exit_status = WEXITSTATUS(status);
	/* 자식 프로세스가 비정상적으로 종료됬다면, 시그널 번호를 저장 */
	else if (WIFSIGNALED(status))
		g_status.global_exit_status = WTERMSIG(status);
	else
		g_status.global_exit_status = EXIT_FAILURE;
	return (0);
}

int	execute_command_subshell(t_list *command_list, char **envp)
{
	char	**argv;
	char	**env;
	char	*path;
	char	*cmd;

	argv = list_to_strs(command_list);
	env = envp;
	if (ft_strchr(argv[0], '/'))
		cmd = argv[0];
	else
	{
		path = get_env_path(env);
		if (!path)
			print_error("execute_command_subshell", "can't PATH= in envp");
		cmd = get_cmd_from_path(argv[0], path);
	}
	if (!cmd)
		print_error("execute_command_subshell", "can't access to command");
	if (execve(cmd, argv, envp) < 0)
		print_error("execute_command_subshell", "execve error");
	return (0);
}
