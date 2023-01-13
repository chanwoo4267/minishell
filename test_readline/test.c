/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwopa <chanwopa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 03:34:30 by chanwopa          #+#    #+#             */
/*   Updated: 2023/01/14 03:54:36 by chanwopa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int	main(void)
{
	char	*in;

	while (1)
	{
		in = readline("minishell:$");
		if (in)
			printf("%s\n", in);
		else
			break ;
		read_history(in);
		free(in);
	}
	return (0);
}
