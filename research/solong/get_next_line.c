/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgu <hgu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 16:38:42 by hgu               #+#    #+#             */
/*   Updated: 2023/09/06 23:30:47 by hgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_fd_list	*head;
	t_fd_list			*node;

	if (head == NULL)
	{
		head = malloc_node(fd, NULL);
		if (head == NULL)
			ft_error("gnl ");
		node = head;
	}
	else
	{
		node = head;
		while (node -> fd != fd && node -> next != NULL)
			node = node -> next;
		if (node -> fd != fd && node -> next == NULL)
		{
			node -> next = malloc_node(fd, node);
			node = node -> next;
		}
	}
	if (node == NULL)
		ft_error("gnl ");
	return (read_value(fd, node, &head));
}

char	*read_value(int fd, t_fd_list *node, t_fd_list **head)
{
	char	buf[BUFFER_SIZE];
	int		read_size;

	while (find_nl(node, BUFFER_SIZE) == 0)
	{
		read_size = read(fd, buf, BUFFER_SIZE);
		if (read_size == -1 || (read_size == 0 && node -> str[0] == '\0'))
		{
			free_node(node, head);
			return (NULL);
		}
		node -> str = ft_strjoin(node -> str, buf, read_size);
		if (node -> str == NULL)
		{
			free_node(node, head);
			ft_error("gnl ");
		}
		if (find_nl(node, read_size) == 2)
			return (ft_end(node -> str, node, head));
	}
	return (ft_nl(node -> str, node, head));
}

int	find_nl(t_fd_list *node, int read_size)
{
	int	idx;

	idx = 0;
	if (read_size < BUFFER_SIZE)
		return (2);
	while (node -> str[idx])
	{
		if (node -> str[idx] == '\n')
			return (1);
		idx++;
	}
	return (0);
}

char	*ft_nl(char *str, t_fd_list *node, t_fd_list **head)
{
	int		idx;
	int		len;
	char	*gnl;
	char	*tmp;

	idx = -1;
	len = 0;
	while (node -> str[len] != '\n')
		len++;
	if (len == ft_strlen(str))
		return (ft_end(str, node, head));
	tmp = make_str(ft_strlen(node -> str) - len, node, head, NULL);
	if (tmp == NULL)
		ft_error("gnl ");
	gnl = make_str(len + 2, node, head, tmp);
	if (gnl == NULL)
		ft_error("gnl ");
	while (++idx <= len)
		gnl[idx] = node -> str[idx];
	len = 0;
	while (idx <= ft_strlen(str))
		tmp[len++] = str[idx++];
	free(str);
	node -> str = tmp;
	return (gnl);
}

char	*ft_end(char *str, t_fd_list *node, t_fd_list **head)
{
	int		idx;
	int		len;
	char	*gnl;

	idx = -1;
	len = 0;
	while (str[len] != '\0')
	{
		if (str[len] == '\n')
			return (ft_nl(str, node, head));
		len++;
	}
	gnl = (char *)malloc(len + 1);
	if (gnl == NULL)
	{
		free_node(node, head);
		ft_error("gnl ");
	}
	while (++idx < len)
		gnl[idx] = node -> str[idx];
	gnl[idx] = '\0';
	free_node(node, head);
	return (gnl);
}
