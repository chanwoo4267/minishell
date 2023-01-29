/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_dollar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjung <sehjung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 15:13:00 by sehjung           #+#    #+#             */
/*   Updated: 2023/01/29 15:21:07 by sehjung          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_dollar	*join_and_free(t_dollar *lst, char *str)
{
	char	*temp;

	temp = lst->temp;
	lst->temp = ft_strjoin(lst->temp, str);
	free(temp);
	temp = NULL;
	return (lst);
}
