/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwopa <chanwopa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 12:40:22 by chanwopa          #+#    #+#             */
/*   Updated: 2023/01/16 16:56:33 by chanwopa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "execution_test.h"

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

static int	identify_builtin(char *str)
{
	if (ft_strncmp(str, "cd", ft_strlen(str)) == 0)
		return (BUILTIN_CD);
	else if (ft_strncmp(str, "echo", ft_strlen(str)) == 0)
		return (BUILTIN_ECHO);
	else if (ft_strncmp(str, "exit", ft_strlen(str)) == 0)
		return (BUILTIN_EXIT);
	else if (ft_strncmp(str, "pwd", ft_strlen(str)) == 0)
		return (BUILTIN_PWD);
	else if (ft_strncmp(str, "export", ft_strlen(str)) == 0)
		return (BUILTIN_EXPORT);
	else if (ft_strncmp(str, "unset", ft_strlen(str)) == 0)
		return (BUILTIN_UNSET);
	else if (ft_strncmp(str, "env", ft_strlen(str)) == 0)
		return (BUILTIN_ENV);
	else
		return (NOT_BUILTIN);
}

int	execute_builtin(t_list *command, t_info *info)
{
	t_token		*token;
	t_builtin	bi;

	token = (t_token *)command->content;
	bi = identify_builtin(token->content);
	if (bi == NOT_BUILTIN)
		return (NOT_BUILTIN);
	/* 함수 포인터 사용으로 간결하게 짤 수 있을듯? */
	else if (bi == BUILTIN_CD)
		builtin_cd(command, info);
	return (1);
}
