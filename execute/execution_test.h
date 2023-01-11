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
#define NO 0
#define YES 1

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

#endif