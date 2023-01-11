/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwopa <chanwopa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 18:40:11 by chanwopa          #+#    #+#             */
/*   Updated: 2023/01/11 18:40:11 by chanwopa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution_test.h"

int	execute_command(t_commandlist *commandlist, t_info *info)
{
	pid_t   pid;
    int     status;

    pid = fork();
    if (pid < 0)
        print_error();
    else if (pid == 0)
    {
        info->issubshell = YES;
        execute_command_subshell(commandlist->command, info->envp);
    }
    if (waitpid(pid, &status, 0) < 0)
        print_Error();
    if (WIFEXITED(status)) /* 자식 프로세스가 정상적으로 종료됬다면, 자식 프로세스의 종료 코드를 저장 */
        g_status.global_exit_status = WEXITSTATUS(status);
    else if (WIFSIGNALED(status)) /* 자식 프로세스가 비정상적으로 종료됬다면, 시그널 번호를 저장 */
        g_status.global_exit_status = WTERMSIG(status);
    else
        g_status.global_exit_status = EXIT_FAILURE;
}

char	*set_env_path(char **env)
{
	char	*path;

	while (*env && ft_strncmp(*env, "PATH=", 5) != 0)
		env++;
	if (*env == NULL)
		path = NULL;
	else
	{
		path = ft_strchr(*p, '=') + 1;
		if (*path == '\0')
			path = NULL;
	}
	return (path);
}

int	get_absolute_cmd(char *cmd, char *path)
{

}

int execute_command_subshell(t_list *command, char **envp)
{
    char    **cmd;
    char    **env;
	char	*path;
	char	*absolute_cmd;

    cmd = list_to_strs(command);
    env = envp;
	if (ft_strchr(cmd[0], '/'))
		execute_given_path(cmd, envp);
	path = set_env_path(env);
	if (path == NULL)
		print_error();
	absolute_cmd = get_absolute_cmd(cmd[0], path);
	if (!absolute_cmd)
		print_error();
	if (execve(absolute_cmd, cmd, envp) < 0)
		print_error();
}

int	execute_given_path(char **cmd, char **envp)
{
	
}
