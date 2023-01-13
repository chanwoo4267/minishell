/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwopa <chanwopa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 17:26:01 by chanwopa          #+#    #+#             */
/*   Updated: 2023/01/14 05:24:19 by chanwopa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "execution_test.h"

#define COMMAND_NUM 2

t_token	*new_token(char *command, t_type type)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	new_token->content = ft_strdup(command);
	new_token->type = type;
	return (new_token);
}

void	init_structs(t_commandlist *test_command, t_info *info, char **envp)
{
	int	i;

	i = 0;
	while (i < COMMAND_NUM + 1)
	{
		test_command[i].command = NULL;
		test_command[i].redirection = NULL;
		i++;
	}
	(info)->envp = envp;
	(info)->fd[0] = STDIN_FILENO;
	(info)->fd[1] = STDOUT_FILENO;
	(info)->fd[2] = STDERR_FILENO;
	(info)->issubshell = NO;
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

int	main(int argc, char **argv, char **envp)
{
	t_commandlist	*test_command;
	t_info			info;

	(void)argc;
	(void)argv;
	test_command = malloc(sizeof(t_commandlist) * (COMMAND_NUM + 1));
	init_structs(test_command, &info, envp);
	/* command */
	ft_lstadd_back(&test_command[0].command, ft_lstnew(new_token("cat", COMMAND)));
	ft_lstadd_back(&test_command[0].redirection, ft_lstnew(new_token("a", REDIR_HEREDOC)));
	ft_lstadd_back(&test_command[0].redirection, ft_lstnew(new_token("a.txt", REDIR_OUT)));
	ft_lstadd_back(&test_command[1].command, ft_lstnew(new_token("cat", COMMAND)));
	ft_lstadd_back(&test_command[1].redirection, ft_lstnew(new_token("b", REDIR_HEREDOC)));
	ft_lstadd_back(&test_command[1].redirection, ft_lstnew(new_token("b.txt", REDIR_OUT)));
	test_command[2].command = NULL;
	test_command[2].redirection = NULL;
	/* command end */
	//print_data(test_command);
	execute(test_command, &info);
}
