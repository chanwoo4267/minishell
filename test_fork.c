/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwopa <chanwopa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 19:47:53 by chanwopa          #+#    #+#             */
/*   Updated: 2023/01/06 19:59:49 by chanwopa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>

void	signal_handler(int sig)
{
	if (sig == SIGINT)
		printf("cltr + c!\n");
	else if (sig == SIGQUIT)
		printf("cltr + \\\n");
	exit(1);
}

int	main(int argc, char **argv, char **envp)
{
	int	pid;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (!pid)
	{
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, signal_handler);
		printf("child process sleep for 10s\n");
		sleep(10);
		printf("child end\n");
	}
	else if (pid)
	{
		printf("parent process wait for child %d\n", pid);
		wait(&pid);
		printf("parent end\n");
	}
}

/* 
SIG_IGN : 시그널을 무시한다.
SIG_DFL : 기본행동을 하도록 한다.
*/