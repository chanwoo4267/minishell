/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjung <sehjung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:49:44 by chanwopa          #+#    #+#             */
/*   Updated: 2023/01/27 17:53:49 by sehjung          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>

# define FAIL 0
# define SUCCESS 1

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

typedef struct s_dollar
{
	int		dollar;
	int		check;
	char	*temp;
	char	*d_temp;
	char	*str;
}	t_dollar;

typedef struct s_info
{
	char	**envp;
	int		fd[3];
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

typedef struct s_global
{
	int		global_exit_status;
}	t_global;

t_global	g_status;

/* signal.c */
void			safe_signal(int sig, void *function);
void			sig_readline(int sig);
void			sig_fork(int mode);
void			sig_process(int sig);
void			init_signal(void);

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

#endif
