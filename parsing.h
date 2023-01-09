/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwopa <chanwopa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:49:44 by chanwopa          #+#    #+#             */
/*   Updated: 2023/01/09 16:01:43 by chanwopa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSINH_H

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_token
{
	char	*content;
	int		type;
	t_token	*next;
}	t_token;

typedef struct s_commandlist
{
	t_list	*command;
	t_list	*redirection;
}	t_commandlist;

#endif