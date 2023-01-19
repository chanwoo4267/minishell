/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwopa <chanwopa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 17:26:01 by chanwopa          #+#    #+#             */
/*   Updated: 2023/01/19 23:18:54 by chanwopa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "execution_test.h"

int	command_n;

t_token	*new_token(char *command, t_type type)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	new_token->content = ft_strdup(command);
	new_token->type = type;
	return (new_token);
}

void	print_data(t_commandlist *commandlist)
{
	t_list	*ptr;
	t_token	*token;
	int		i;

	i = 0;
	while (commandlist[i].command != NULL)
	{
		printf("---command %d---\n", i);
		ptr = commandlist[i].command;
		while (ptr)
		{
			token = (t_token *)(ptr->content);
			printf("%s %d\n", token->content, token->type);
			ptr = ptr->next;
		}
		ptr = commandlist[i].redirection;
		while (ptr)
		{
			token = (t_token *)(ptr->content);
			printf("%s %d\n", token->content, token->type);
			ptr = ptr->next;
		}
		printf("---command %d end---\n", i);
		i++;
	}
}

void	print_envp(char **envp)
{
	int	i;

	i = 0;
	if (envp)
	{
		printf("---envp start---\n");
		while (envp[i])
		{
			printf("%s\n", envp[i]);
			i++;
		}
		printf("---envp end---\n");
	}
}

char	**set_envp(char **envp)
{
	char	**new_envp;
	int		i;

	if (!envp)
		print_error("set_envp", "no envp");
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

void	init_structs(t_commandlist *test_command, t_info *info, char **envp)
{
	int	i;

	i = 0;
	while (i < command_n + 1)
	{
		test_command[i].command = NULL;
		test_command[i].redirection = NULL;
		i++;
	}
	(info)->envp = set_envp(envp);
	(info)->fd[0] = dup(STDIN_FILENO);
	(info)->fd[1] = dup(STDOUT_FILENO);
	(info)->fd[2] = dup(STDERR_FILENO);
	(info)->issubshell = NO;
}

int	main(int argc, char **argv, char **envp)
{
	t_commandlist	*test_command;
	t_info			info;

	command_n = 1;
	(void)argc;
	(void)argv;
	test_command = malloc(sizeof(t_commandlist) * (command_n + 1));
	init_structs(test_command, &info, envp);
	/* command */
	ft_lstadd_back(&test_command[0].command, ft_lstnew(new_token("echo", COMMAND)));
	ft_lstadd_back(&test_command[0].command, ft_lstnew(new_token("-nnnnn", COMMAND)));
	ft_lstadd_back(&test_command[0].command, ft_lstnew(new_token("-nnn", COMMAND)));
	ft_lstadd_back(&test_command[0].command, ft_lstnew(new_token("-n-n-n-n", COMMAND)));
	ft_lstadd_back(&test_command[0].command, ft_lstnew(new_token("-nnnnn", COMMAND)));
	ft_lstadd_back(&test_command[0].command, ft_lstnew(new_token("--nnn", COMMAND)));
	/* command end */
	execute(test_command, &info);
}


/* command "cat << a > a.txt | cat << b > b.txt"
	ft_lstadd_back(&test_command[0].command, ft_lstnew(new_token("cat", COMMAND)));
	ft_lstadd_back(&test_command[0].redirection, ft_lstnew(new_token("a", REDIR_HEREDOC)));
	ft_lstadd_back(&test_command[0].redirection, ft_lstnew(new_token("a.txt", REDIR_OUT)));
	ft_lstadd_back(&test_command[1].command, ft_lstnew(new_token("cat", COMMAND)));
	ft_lstadd_back(&test_command[1].redirection, ft_lstnew(new_token("b", REDIR_HEREDOC)));
	ft_lstadd_back(&test_command[1].redirection, ft_lstnew(new_token("b.txt", REDIR_OUT)));

	ft_lstadd_back(&test_command[0].command, ft_lstnew(new_token("env", COMMAND)));
	ft_lstadd_back(&test_command[1].command, ft_lstnew(new_token("cat", COMMAND)));

	ft_lstadd_back(&test_command[0].command, ft_lstnew(new_token("env", COMMAND)));
	ft_lstadd_back(&test_command[1].command, ft_lstnew(new_token("cat", COMMAND)));
	ft_lstadd_back(&test_command[1].redirection, ft_lstnew(new_token("a.txt", REDIR_OUT)));
	ft_lstadd_back(&test_command[2].command, ft_lstnew(new_token("pwd", COMMAND)));
*/
