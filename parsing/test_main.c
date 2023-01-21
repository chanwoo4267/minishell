/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjung <sehjung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 18:48:08 by sehjung           #+#    #+#             */
/*   Updated: 2023/01/21 21:10:01 by sehjung          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int main(int argc, char **argv, char **envp)
{
	char *str;
	t_commandlist *lst;
	t_list *c_lst;
	t_list *r_lst;

	while (1)
	{
		str = readline("$>");
		lst = parsing(str, envp);
		if (!lst)
			continue;
		c_lst = lst[0].command;
		r_lst = lst[0].redirection;
		while (c_lst)
		{
			printf("%s, TYPE : %d\n", ((t_token*)c_lst->content)->content, ((t_token*)c_lst->content)->type);
			c_lst = c_lst->next;
		}
		while (r_lst)
		{
			printf("%s, TYPE : %d\n", ((t_token*)r_lst->content)->content, ((t_token*)r_lst->content)->type);
			r_lst = r_lst->next;
		}
	}
}