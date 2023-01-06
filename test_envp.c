/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwopa <chanwopa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 19:36:54 by chanwopa          #+#    #+#             */
/*   Updated: 2023/01/06 19:38:55 by chanwopa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int	main(int argc, char **argv, char **envp)
{
	char	*ptr;
	int		i;

	i = 0;
	ptr = envp[i];
	while (ptr)
	{
		printf("%s\n", ptr);
		ptr = envp[++i];
	}
	return (0);
}
