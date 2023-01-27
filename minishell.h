/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjung <sehjung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 15:38:32 by chanwopa          #+#    #+#             */
/*   Updated: 2023/01/27 17:57:47 by sehjung          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <sys/wait.h>
# include <sys/signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <termios.h>

/*** define list start ***/
# define FAIL 0
# define SUCCESS 1
# define NO 0
# define YES 1
# define SUBSHELL 0
# define HEREDOC 1
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
	DOLLAR_SIGN
}	t_type;

typedef enum e_builtin
{
	NOT_BUILTIN,
	BUILTIN_ECHO,
	BUILTIN_CD,
	BUILTIN_EXIT,
	BUILTIN_PWD,
	BUILTIN_EXPORT,
	BUILTIN_UNSET,
	BUILTIN_ENV,
}	t_builtin;

typedef struct s_dollar
{
	int		dollar;
	int		check;
	char	*temp;
	char	*d_temp;
	char	*str;
}	t_dollar;

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
}	t_global;
/*** struct list end ***/

t_global	g_status;

/*** function list start ***/
/* execute.c */
int				execute(t_commandlist *commandlist, t_info *info);
int				execute_subshell(t_commandlist commandlist, t_info *info);
int				execute_pipe(t_commandlist *commandlist, \
							t_info *info, int cmd_count);
int				reset_redirection(t_info *info);

/* execute_utils.c */
char			**list_to_strs(t_list *command);
int				get_commands_count(t_commandlist *commandlist);

/* envp_utils.c */
char			**set_envp(char **envp);
void			change_envp(char *new, t_info *info);
void			add_envp(char *new, t_info *info);
void			delete_envp(char *del, t_info *info);

/* execute_command.c */
void			execute_command(t_list *command, t_info *info);
void			execute_command_subshell(t_list *command_list, char **envp);

/* execute_redir.c */
int				redirection(t_list *redirection);

/* execute_heredoc.c */
int				redirect_heredoc(t_commandlist *commandlist, int cmd_count);

/* execute_builtin.c */
int				execute_builtin(t_list *command, t_info *info);

/* execute_pipe.c */
int				execute_pipe(t_commandlist *commandlist, \
							t_info *info, int cmd_count);

/* execute_test.c */
void			print_data(t_commandlist *commandlist);
void			print_envp(char **envp);

/* execute_builtin.c */
int				execute_builtin(t_list *command, t_info *info);

/* builtin */
void			builtin_cd(t_list *command, t_info *info);
void			builtin_echo(t_list *list);
void			builtin_pwd(t_list *list);
void			builtin_export(t_list *list, t_info *info);
void			builtin_exit(t_list *list);
void			builtin_unset(t_list *list, t_info *info);
void			builtin_env(t_list *list, t_info *info);

/* signal.c */
void			safe_signal(int sig, void *function);
void			sig_readline(int sig);
void			sig_fork(int mode);
void			sig_process(int sig);
void			init_signal(void);

/* error.c */
void			print_error(char *command, char *input, \
							char *message, int err_status);
void			system_error(char *str1, char *str2, int error_code);

/* free.c */
void			free_strs(char **strs);
void			free_lists(t_list *list);
void			free_commands(t_commandlist *commandlist);

/* ascii_change.c */
void			ascii_change(char **str);

/* convert_dollar.c */
char			*convert_dollar(char *str, char **envp);

/* dollar_utils.c */
char			*free_dollar(t_dollar *lst, char *ret);
t_dollar		*convert_envp(t_dollar *lst, char **envp);
t_dollar		*init_dollar(char *str);
char			*envp_to_str(char *str, char **envp, int i);
int				find_dollar(char *str);

/*  exception_line.c */
char			*exception_line(char *line);

/* exception_utils.c */
int				syntax_pipe(char *line);
int				syntax_redirect(char *line);

/* parsing_redrect.c */
t_list			*redirect_in(char **str, int i, char **envp);
t_list			*redirect_out(char **str, int i, char **envp);

/* parsing_utils.c */
int				count_pipe(char *str);
int				check_whitespace(char c);
char			*ft_strjoin_char(char *s1, char s2);
t_token			*new_token(char *command, t_type type);
t_commandlist	*init_parsing(char **str, t_commandlist *lst, char **envp);
t_commandlist	*parsing(char *line, char **envp);

/*** function list end ***/

#endif