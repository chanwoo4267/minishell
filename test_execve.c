/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_execve.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwopa <chanwopa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 19:40:42 by chanwopa          #+#    #+#             */
/*   Updated: 2023/01/06 19:44:19 by chanwopa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int	main(int argc, char **argv, char **envp)
{
	char	*ptr;
	int		i;

	execve("/bin/ls", argv, envp);
}

//int execve(const char *path, char const **argv, char const **envp)