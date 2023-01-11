/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwopa <chanwopa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 17:26:01 by chanwopa          #+#    #+#             */
/*   Updated: 2023/01/11 23:06:54 by chanwopa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "execution_test.h"

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
	while (i < 3)
	{
		test_command[i].command = NULL;
		test_command[i].redirection = NULL;
		i++;
	}
	(info)->envp = envp;
	(info)->fd[0] = STDIN_FILENO;
	(info)->fd[1] = STDOUT_FILENO;
	(info)->fd[2] = STDERR_FILENO;
	(info)->issubshell = 0;
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
	((t_token *)(commandlist[1].command->content))->content = "hello world";
}

int	main(int argc, char **argv, char **envp)
{
	t_commandlist	*test_command;
	t_info			info;

	(void)argc;
	(void)argv;
	test_command = malloc(sizeof(t_commandlist) * 3);
	init_structs(test_command, &info, envp);
	/* ls -al > a.txt | echo -n < b.txt > c.txt */
	/*
	ft_lstadd_back(&test_command[0].command, ft_lstnew(new_token("ls", COMMAND)));
	ft_lstadd_back(&test_command[0].command, ft_lstnew(new_token("-al", COMMAND)));
	ft_lstadd_back(&test_command[0].redirection, ft_lstnew(new_token("a.txt", REDIR_OUT)));
	ft_lstadd_back(&test_command[1].command, ft_lstnew(new_token("echo", COMMAND)));
	ft_lstadd_back(&test_command[1].command, ft_lstnew(new_token("-n", COMMAND)));
	ft_lstadd_back(&test_command[1].redirection, ft_lstnew(new_token("b.txt", REDIR_IN)));
	ft_lstadd_back(&test_command[1].redirection, ft_lstnew(new_token("c.txt", REDIR_OUT)));
	test_command[2].command = NULL;
	test_command[2].redirection = NULL;
	*/
	ft_lstadd_back(&test_command[0].command, ft_lstnew(new_token("ls", COMMAND)));
	ft_lstadd_back(&test_command[0].command, ft_lstnew(new_token("-al", COMMAND)));
	ft_lstadd_back(&test_command[0].redirection, ft_lstnew(new_token("a.txt", REDIR_OUT)));
	test_command[1].command = NULL;
	test_command[1].redirection = NULL;
	//print_data(test_command);
	execute(test_command, &info);
}
