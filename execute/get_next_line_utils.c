/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwopa <chanwopa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 01:11:45 by chanwopa          #+#    #+#             */
/*   Updated: 2022/12/13 22:12:27 by chanwopa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*p;

	i = 0;
	while (s1[i])
		i++;
	p = malloc(sizeof(char) * (i + 1));
	if (!p)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	i;
	char	*str;

	i = 0;
	while (s1[i])
		i++;
	s1_len = i;
	i = 0;
	while (s2[i])
		i++;
	s2_len = i;
	str = malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!str)
		return (NULL);
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	i--;
	while (s2[++i - s1_len])
		str[i] = s2[i - s1_len];
	str[i] = '\0';
	return (str);
}

char	*gnl_strlcpy(char *dst, const char *src, size_t count)
{
	char	*remain_str;
	size_t	i;
	size_t	l_count;

	i = 0;
	if (!dst || !src)
		return (NULL);
	while (src[i])
		i++;
	l_count = i - count;
	remain_str = malloc(sizeof(char) * (l_count + 1));
	if (!remain_str)
		return (NULL);
	i = -1;
	while (++i < count)
		dst[i] = src[i];
	dst[i] = '\0';
	i = -1;
	while (++i < l_count)
		remain_str[i] = src[count + i];
	remain_str[i] = '\0';
	return (remain_str);
}	

char	*find_newline(char *joined_str, char **current_str)
{
	size_t	i;
	char	*return_str;
	char	*remain_str;

	i = 0;
	free(*current_str);
	while (joined_str[i] && joined_str[i] != '\n')
		i++;
	if (!joined_str[i])
	{
		*current_str = joined_str;
		return (joined_str);
	}
	else
	{
		return_str = malloc(sizeof(char) * (i + 2));
		remain_str = gnl_strlcpy(return_str, joined_str, i + 1);
		if (!remain_str)
			return (NULL);
		free(joined_str);
		*current_str = remain_str;
		return (return_str);
	}
}

void	destroy_current_node(t_llist **list_head, int fd)
{
	t_llist	*ptr;
	t_llist	*ptr_before;

	ptr = *list_head;
	if (ptr->fd == fd)
	{
		*list_head = ptr->next;
		free(ptr->str);
		free(ptr);
	}
	else
	{
		while (ptr->fd != fd)
		{
			ptr_before = ptr;
			ptr = ptr->next;
		}
		ptr_before->next = ptr->next;
		free(ptr->str);
		free(ptr);
	}
	return ;
}
