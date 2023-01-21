/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwopa <chanwopa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 15:26:04 by chanwopa          #+#    #+#             */
/*   Updated: 2023/01/21 17:56:51 by chanwopa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**set_envp(char **envp)
{
	char	**new_envp;
	int		i;

	if (!envp)
	{
		new_envp = malloc(sizeof(char *) * 1);
		new_envp[0] = NULL;
		return (new_envp);
	}
	i = 0;
	while (envp[i])
		i++;
	new_envp = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (envp[i])
	{
		new_envp[i] = ft_strdup(envp[i]);
		i++;
	}
	new_envp[i] = NULL;
	return (new_envp);
}

static void	init_info(t_info *info, char **envp)
{
	info->envp = set_envp(envp);
	info->fd[0] = dup(STDIN_FILENO);
	info->fd[1] = dup(STDOUT_FILENO);
	info->fd[2] = dup(STDERR_FILENO);
	info->issubshell = NO;
	g_status.global_exit_status = 0;
}

static void	free_lists(t_list *list)
{
	t_list	*ptr;
	t_list	*remover;

	ptr = list;
	while (ptr)
	{
		remover = ptr;
		ptr = ptr->next;
		if (remover->content)
			free(remover->content);
		if (remover)
			free(remover);
	}
}

static void	free_commands(t_commandlist *commandlist)
{
	int				i;

	if (!commandlist)
		return ;
	i = 0;
	while (commandlist[i].command)
	{
		free_lists(commandlist[i].command);
		free_lists(commandlist[i].redirection);
		i++;
	}
	free(commandlist);
}

static void	terminal_loop(t_info *info)
{
	t_commandlist	*commands;
	char			*input;

	while (1)
	{
		if (signal(SIGINT, sig_readline) == SIG_ERR)
			error_exit("terminal_loop, signal error", 1);
		input = readline("minishell$ ");
		add_history(input);
		if (!input)
			exit(0);
		commands = parsing(input);
		if (commands)
		{
			if (signal(SIGINT, sig_process) == SIG_ERR)
				error_exit("terminal_loop, signal error", 1);
			execute(commands, info);
		}
		else
			error_return("parsing error", 1);
		free(input);
		free_commands(commands);
	}
}

void	test(void)
{
	system("leaks minishell");
}

int	main(int argc, char **argv, char **envp)
{
	t_info			info;

	//atexit(test);
	(void)argc;
	(void)argv;
	init_info(&info, envp);
	init_signal();
	terminal_loop(&info);
	return (0);
}
