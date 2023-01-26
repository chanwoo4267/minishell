/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwopa <chanwopa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 15:26:04 by chanwopa          #+#    #+#             */
/*   Updated: 2023/01/26 20:21:39 by chanwopa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_info(t_info *info, char **envp)
{
	if (!envp)
		system_error("init_info", "cannot receive envp", 1);
	info->envp = set_envp(envp);
	info->fd[0] = dup(STDIN_FILENO);
	info->fd[1] = dup(STDOUT_FILENO);
	info->fd[2] = dup(STDERR_FILENO);
	info->issubshell = NO;
	g_status.global_exit_status = 0;
}

static void	remove_heredoc_tempfiles(void)
{
	char	*str;
	char	*itoa;
	int		i;

	i = 0;
	while (++i <= 32)
	{
		itoa = ft_itoa(i);
		str = ft_strjoin(".heredoc_tmp", itoa);
		if (!itoa || !str)
			system_error("remove_heredoc_tempfiles", "malloc error", 1);
		if (access(str, F_OK) == 0)
			unlink(str);
		free(itoa);
		free(str);
	}
}

static void	terminal_loop(t_info *info)
{
	t_commandlist	*commands;
	char			*input;

	while (1)
	{
		if (signal(SIGINT, sig_readline) == SIG_ERR)
			system_error("terminal_loop", "signal error", 1);
		input = readline("minishell$ ");
		add_history(input);
		if (!input)
			system_error(NULL, "exit", 0);
		commands = parsing(input, info->envp);
		if (commands)
		{
			if (signal(SIGINT, sig_process) == SIG_ERR)
				system_error("terminal_loop", "signal error", 1);
			execute(commands, info);
			free_commands(commands);
			remove_heredoc_tempfiles();
		}
		else
			print_error("syntax error", NULL, NULL, NO);
		free(input);
	}
}

/*
void	test(void)
{
	system("leaks minishell");
}
*/

int	main(int argc, char **argv, char **envp)
{
	t_info	info;

	//atexit(test);
	(void)argc;
	(void)argv;
	init_info(&info, envp);
	init_signal();
	terminal_loop(&info);
	return (0);
}
