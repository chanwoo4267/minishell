/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjung <sehjung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:49:44 by chanwopa          #+#    #+#             */
/*   Updated: 2023/01/21 21:17:18 by sehjung          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>

# define FAIL 0
# define SUCCESS 1

typedef enum e_type
{
	COMMAND,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC,
	DOLLAR_SIGN
}	t_type;

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
/*** struct list end ***/

t_global	g_status;

t_commandlist	*parsing(char *str, char **envp);
t_token			*new_token(char *command, t_type type);
t_list			*redirect_out(char **str, int i, char **envp);
t_list			*redirect_in(char **str, int i, char **envp);
t_list			*convert_envp(char *str, char **envp, t_type type);
int				count_pipe(char *str);
int				check_whitespace(char c);
int				count_pipe(char *str);
char			*ft_strjoin_char(char *s1, char s2);
char			*exception_line(char *line);
void			ascii_change(char **str);
void			remove_special_char(char **str);
void			free_parsing_str(char *str, char **split_str);
void			free_list(t_commandlist *lst);

#endif
