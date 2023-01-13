/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwopa <chanwopa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 12:57:13 by chanwopa          #+#    #+#             */
/*   Updated: 2023/01/13 18:49:37 by chanwopa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "execution_test.h"

int	execute_pipe(t_commandlist *commandlist, t_info *info, int cmd_count)
{
	pid_t	*child_pids;
	int		*pipes;
	int		child_i;
	int		fd_i;

	init_pipes(cmd_count, &child_pids, &pipes);
	build_pipeline(cmd_count, &child_pids, &pipes);
}

void	init_pipes(int cmd_count, pid_t **pids, int ***pipes)
{
	int	i;

	(*pids) = malloc(sizeof(pid_t) * cmd_count);
	(*pipes) = malloc(sizeof(int *) * (cmd_count - 1));
	if (!(*pids) || !(*pipes))
		print_error("init_pipes", "malloc error");
	i = -1;
	while (++i < cmd_count - 1)
	{
		(*pipes)[i] = malloc(sizeof(int) * 2);
		if (!((*pipes)[i]))
			print_error("init_pipes", "submalloc error");
	}
}

void	build_pipeline(int cmd_count, pid_t **pids, int ***pipes)
{
	int	i;

	i = -1;
	while (++i < cmd_count - 1)
	{
		if (pipe((*pipes)[i]) < 0)
			print_error("build_pipeline", "pipe error");
	}
	i = -1;
	while (++i < cmd_count)
	{
		(*pids)[i] = fork();
		if ((*pids)[i] < 0)
			print_error("build_pipeline", "fork error");
		else if ((*pids)[i] == 0)
		{
			set_pipeline(i, cmd_count, *pipes);
			break ;
		}
	}
}
