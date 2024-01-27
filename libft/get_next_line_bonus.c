/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee2 <donglee2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:58:01 by donglee2          #+#    #+#             */
/*   Updated: 2024/01/19 19:04:12 by donglee2         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*rm_node(int fd, t_list_gnl **head_node_ptr)
{
	t_list_gnl	*cur_node;
	t_list_gnl	*prev_node;

	cur_node = *head_node_ptr;
	if (cur_node->fd_num == fd)
	{
		*head_node_ptr = cur_node->next;
		free (cur_node->save);
		free (cur_node);
		return (NULL);
	}
	while (cur_node)
	{
		if (cur_node->fd_num == fd)
			break ;
		prev_node = cur_node;
		cur_node = cur_node->next;
	}
	prev_node->next = cur_node->next;
	free(cur_node->save);
	free(cur_node);
	return (NULL);
}

t_list_gnl	*find_node(int fd, t_list_gnl **head_node_ptr)
{
	t_list_gnl	*cur_node;
	t_list_gnl	*new_node;

	cur_node = *head_node_ptr;
	while (cur_node)
	{
		if (cur_node->fd_num == fd)
			return (cur_node);
		if (!(cur_node->next))
			break ;
		cur_node = cur_node->next;
	}
	new_node = (t_list_gnl *)malloc(sizeof(t_list_gnl));
	if (!new_node)
		return (NULL);
	new_node->next = NULL;
	new_node->save = NULL;
	new_node->fd_num = fd;
	if (!cur_node)
		*head_node_ptr = new_node;
	else
		cur_node->next = new_node;
	return (new_node);
}

char	*cut_line(int fd, t_list_gnl **head_node_ptr, t_list_gnl *node)
{
	char	*ret_line;
	char	*tmp;
	ssize_t	idx;

	idx = ft_strchr_idx(node->save, '\n');
	if (idx == -1)
		idx = ft_strchr_idx(node->save, '\0');
	ret_line = ft_substr(node->save, 0, idx + 1);
	if (!ret_line)
	{
		free(node->save);
		node->save = NULL;
		return (rm_node(fd, head_node_ptr));
	}
	tmp = ft_substr(node->save, idx + 1, ft_strlen(node->save));
	free(node->save);
	if (!tmp)
	{
		node->save = NULL;
		free(ret_line);
		return (rm_node(fd, head_node_ptr));
	}
	node->save = tmp;
	return (ret_line);
}

int	add_line(int read_ret, char **save, char *buff)
{
	char	*tmp;

	if (read_ret == -1 || (read_ret == 0 && !(**save)))
	{
		free(*save);
		*save = NULL;
		return (1);
	}
	buff[read_ret] = '\0';
	if (read_ret == 0)
		return (-1);
	tmp = ft_strjoin(*save, buff);
	free (*save);
	*save = (NULL);
	if (!tmp)
		return (1);
	*save = tmp;
	return (0);
}

char	*get_next_line(int fd)
{
	char				buff[BUFFER_SIZE + 1];
	static t_list_gnl	*head_node;
	t_list_gnl			*cur_node;
	int					tmp;

	cur_node = find_node(fd, &head_node);
	if (!cur_node)
		return (NULL);
	if (!(cur_node->save))
		cur_node->save = ft_strdup("");
	if (!(cur_node->save))
	{
		rm_node(fd, &head_node);
		return (NULL);
	}
	while (ft_strchr_idx(cur_node->save, '\n') < 0)
	{
		tmp = add_line(read(fd, buff, BUFFER_SIZE), &(cur_node->save), buff);
		if (tmp == -1)
			break ;
		if (tmp)
			return (rm_node(fd, &head_node));
	}
	return (cut_line(fd, &head_node, cur_node));
}

// #include <fcntl.h>
// #include <stdio.h>

// int main()
// {
// 	int fd3 = open("3.txt", O_RDONLY | O_CREAT, 0644);
// 	int fd4 = open("4.txt", O_RDONLY | O_CREAT, 0644);
// 	int fd5 = open("5.txt", O_RDONLY | O_CREAT, 0644);

// 	char	*new_line;
// 	for(int i = 0; i < 3; i++)
// 	{
// 		new_line = get_next_line(fd3);
// 		printf("%s", new_line);
// 		free(new_line);
// 	}
// 	for(int i = 0; i < 3; i++)
// 	{
// 		new_line = get_next_line(fd4);
// 		printf("%s", new_line);
// 		free(new_line);
// 	}	for(int i = 0; i < 3; i++)
// 	{
// 		new_line = get_next_line(fd5);
// 		printf("%s", new_line);
// 		free(new_line);
// 	}
// }