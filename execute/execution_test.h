/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_test.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwopa <chanwopa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 17:26:33 by chanwopa          #+#    #+#             */
/*   Updated: 2023/01/10 17:26:33 by chanwopa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_TEST_H
# define EXECUTION_TEST_H

#include "../libft/libft.h"
#include "../get_next_line/get_next_line.h"

#define FAIL 0
#define SUCCESS 1

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

#endif