/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_test.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwopa <chanwopa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 17:26:33 by chanwopa          #+#    #+#             */
/*   Updated: 2023/01/12 17:27:54 by chanwopa         ###   ########seoul.kr  */
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

# define FAIL 0
# define SUCCESS 1
# define NO 0
# define YES 1

typedef enum e_type
{
	COMMAND,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC,
}	t_type;

/* 환경변수, STD FD 저장, 현재 프로세스가 subshell인지 아닌지 판단하는 플래그 */
typedef struct s_info
{
	char	**envp;
	int		fd[3];
	int		issubshell;
}	t_info;

typedef struct s_token
{
	char	*content;
	int		type;
}	t_token;

typedef struct s_commandlist
{
	t_list	*command;
	t_list	*redirection;
}	t_commandlist;

/* 가장 최근 프로세스의 종료 상태를 저장하기 위한 전역변수 */
typedef struct s_globalstatus
{
	int	global_exit_status;
}	t_globalstatus;

t_globalstatus	g_status;

/* functions */
int		execute(t_commandlist *commandlist, t_info *info);
int		execute_subshell(t_commandlist commandlist, t_info *info);
int		execute_pipe(t_commandlist *commandlist, t_info *info);
int		reset_redirection(t_info *info);

char	**list_to_strs(t_list *command);
void	print_error(void);

int		execute_command(t_list *command, t_info *info);
char	*get_env_path(char **env);
char	*get_absolute_cmd(char *name, char *path);
int		execute_command_subshell(t_list *command, char **envp);
int		execute_given_path(char **cmd, char **envp);

int		redirection(t_list	*redirection);
void	redirect_input(char *filename);
void	redirect_output(char *filename);
void	redirect_append(char *filename);
void	redirect_heredoc(char *delimiter);

/* test functions */
void	print_data(t_commandlist *commandlist);

#endif