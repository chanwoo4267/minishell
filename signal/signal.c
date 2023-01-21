/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwopa <chanwopa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 16:35:59 by chanwopa          #+#    #+#             */
/*   Updated: 2023/01/21 17:20:36 by chanwopa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sig_readline(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
	g_status.global_exit_status = sig;
}

void	sig_fork(void)
{
	if (signal(SIGINT, SIG_DFL) == SIG_ERR)
		error_exit("signal handler error", 1);
	if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
		error_exit("signal handler error", 1);
}

void	sig_process(int sig)
{
	if (sig == SIGINT)
		printf("\n");
}

void	init_signal(void)
{
	struct termios	s_term;

	if (tcgetattr(STDIN_FILENO, &s_term) == -1)
		error_exit("signal init error", 1);
	s_term.c_lflag &= ~(ECHOCTL);
	if (tcsetattr(STDIN_FILENO, TCSANOW, &s_term) == -1)
		error_exit("signal init error", 1);
	if (signal(SIGINT, sig_readline) == SIG_ERR)
		error_exit("signal handler error", 1);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		error_exit("signal handler error", 1);
}
