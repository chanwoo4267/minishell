/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanwopa <chanwopa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 01:11:54 by chanwopa          #+#    #+#             */
/*   Updated: 2022/12/13 22:12:13 by chanwopa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_llist	*find_current_node(t_llist **list_head, ssize_t fd)
{
	t_llist	*ptr;
	t_llist	*new_node;

	if (*list_head)
	{
		ptr = (*list_head);
		while (ptr)
		{
			if (ptr->fd == fd)
				return (ptr);
			ptr = ptr->next;
		}
	}
	new_node = malloc(sizeof(t_llist));
	if (!new_node)
		return (NULL);
	new_node->fd = fd;
	new_node->next = NULL;
	new_node->str = ft_strdup("");
	if (!(new_node->str))
		return (NULL);
	if (*list_head)
		new_node->next = (*list_head);
	(*list_head) = new_node;
	return (new_node);
}

char	*non_full_read(t_varcollection *dump, t_llist **list_head, \
						int fd, int mode)
{
	dump->buffer[dump->read_bytes] = '\0';
	if (mode == 0 || (mode == 1 && (dump->current)->str[0] == '\0'))
	{
		destroy_current_node(list_head, fd);
		return (NULL);
	}
	dump->joined_str = gnl_strjoin((dump->current)->str, dump->buffer);
	dump->joined_str = find_newline(dump->joined_str, &((dump->current)->str));
	if (!(dump->joined_str))
		return (NULL);
	if (dump->joined_str == (dump->current)->str)
	{
		dump->joined_str = ft_strdup(dump->joined_str);
		destroy_current_node(list_head, fd);
	}
	return (dump->joined_str);
}

void	full_read(t_varcollection *dump)
{
	dump->buffer[dump->read_bytes] = '\0';
	dump->joined_str = gnl_strjoin((dump->current)->str, dump->buffer);
	dump->joined_str = find_newline(dump->joined_str, &((dump->current)->str));
	if (!(dump->joined_str))
		dump->flags = 0;
	else if (dump->joined_str == (dump->current)->str)
		dump->flags = 1;
	else
		dump->flags = 2;
}

char	*loop_function(t_varcollection *dump, t_llist **list_head, int fd)
{
	while (1)
	{
		dump->read_bytes = read(fd, dump->buffer, BUFFER_SIZE);
		if (dump->read_bytes < 0)
			return (non_full_read(dump, list_head, fd, 0));
		else if (dump->read_bytes == 0)
			return (non_full_read(dump, list_head, fd, 1));
		else if (dump->read_bytes < BUFFER_SIZE)
			return (non_full_read(dump, list_head, fd, 2));
		else
		{
			full_read(dump);
			if (dump->flags == 0)
				return (NULL);
			else if (dump->flags == 1)
				continue ;
			else
				return (dump->joined_str);
		}
	}
}

char	*get_next_line(int fd)
{
	static t_llist	*list_head;
	t_varcollection	dump;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	dump.current = find_current_node(&list_head, fd);
	if (!(dump.current))
		return (NULL);
	return (loop_function(&dump, &list_head, fd));
}
