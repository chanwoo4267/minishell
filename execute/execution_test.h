/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_test.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwopa <chanwopa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 17:26:33 by chanwopa          #+#    #+#             */
/*   Updated: 2023/01/16 16:38:17 by chanwopa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_TEST_H
# define EXECUTION_TEST_H

# include "../libft/libft.h"
# include "get_next_line.h"
# include <stdio.h>
# include <sys/wait.h>
# include <sys/signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

/*** define list start ***/
# define FAIL 0
# define SUCCESS 1
# define NO 0
# define YES 1
/*** define list end ***/

/*** struct list start ***/
/* REDIR_IN, REDIR_OUT 을 0,1로 설정해서 redirection에 이용함 */
typedef enum e_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC,
	COMMAND,
	PIPE,
	ASSIGN_SHELL_VAR,
}	t_type;

/* issubshell must be set NO when initializing main function */
typedef struct s_info
{
	char	**envp;
	int		fd[3];
	int		issubshell;
}	t_info;

typedef struct s_token
{
	char	*content;
	t_type	type;
}	t_token;

typedef struct s_commandlist
{
	t_list	*command;
	t_list	*redirection;
}	t_commandlist;

/* 가장 최근 프로세스의 종료 상태를 저장하기 위한 전역변수 */
typedef struct s_global
{
	int		global_exit_status;
	t_info	*g_info;
}	t_global;
/*** struct list end ***/

t_global	g_status;

/*** function list start ***/
/* execute.c */
int		execute(t_commandlist *commandlist, t_info *info);
int		execute_subshell(t_commandlist commandlist, t_info *info, int cmd_idx);
int		execute_pipe(t_commandlist *commandlist, t_info *info, int cmd_count);
int		reset_redirection(t_info *info);

/* execute_utils.c */
char	**list_to_strs(t_list *command);
void	print_error(char *location, char *message);
void	print_message(char *message);
int		get_commands_count(t_commandlist *commandlist);

/* execute_command.c */
int		execute_command(t_list *command, t_info *info);
int		execute_command_subshell(t_list *command_list, char **envp);

/* execute_redir.c */
int		redirection(t_list	*redirection, int cmd_idx);

/* execute_builtin.c */
int		execute_builtin(t_list *command, t_info *info);

/* execute_pipe.c */
int		execute_pipe(t_commandlist *commandlist, t_info *info, int cmd_count);

/* execute_test.c */
void	print_data(t_commandlist *commandlist);

/* execute_builtin.c */
int		execute_builtin(t_list *command, t_info *info);

/* builtin */
void	builtin_cd(t_list *command, t_info *info);
/*** function list end ***/

#endif