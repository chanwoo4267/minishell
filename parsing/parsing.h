/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjung <sehjung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:49:44 by chanwopa          #+#    #+#             */
/*   Updated: 2023/01/13 16:30:21 by sehjung          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

#define FAIL 0
#define SUCCESS 1

#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>

typedef enum e_type
{
	COMMAND,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC,
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

t_commandlist	*parsing(char *str);
t_token	*new_token(char *command, t_type type);
void	remove_special_char(char **str);
int	count_pipe(char *str);
void	free_list(t_commandlist *lst);

// typedef struct s_token t_token;
// typedef struct s_list t_list;

// // typedef struct s_list
// // {
// // 	void			*content;
// // 	struct t_list	*next;
// // }	t_list;

// typedef struct s_info
// {
// 	char	**envp;
// 	int		fd[3];
// }	t_info;

// typedef struct s_token
// {
// 	char	*content;
// 	int		type;
// 	t_token	*next;
// }	t_token;

// typedef struct s_commandlist
// {
//     t_list  *command; //"ls" "-al"
//     t_list  *redirection; //"a.txt"(>) "b.txt"(>) "c.txt"(<) "d.txt"(>>)
// }   t_commandlist;

#endif