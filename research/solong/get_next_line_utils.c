/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgu <hgu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 16:01:19 by hgu               #+#    #+#             */
/*   Updated: 2023/09/02 21:44:41 by hgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *s)
{
	int	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

char	*ft_strjoin(char *s1, char *s2, int read_size)
{
	char	*s3;
	int		len;
	int		len1;

	if (read_size == 0)
		return (s1);
	if (s2 == NULL)
		return (s1);
	len = -1;
	len1 = ft_strlen(s1);
	s3 = (char *)malloc(len1 + read_size + 1);
	if (s3 == NULL)
	{	
		free(s1);
		return (NULL);
	}
	while (++len < len1)
		s3[len] = s1[len];
	len = -1;
	while (++len < read_size)
		s3[len + len1] = s2[len];
	s3[len + len1] = '\0';
	free(s1);
	return (s3);
}

t_fd_list	*malloc_node(int fd, t_fd_list *prev)
{
	t_fd_list			*node;

	node = (t_fd_list *)malloc(sizeof(t_fd_list));
	if (node == NULL)
		return (NULL);
	node -> fd = fd;
	node -> str = (char *)malloc(1);
	if (node -> str == NULL)
	{
		free(node);
		return (NULL);
	}
	node -> str[0] = 0;
	node -> prev = prev;
	node -> next = NULL;
	return (node);
}

void	free_node(t_fd_list *node, t_fd_list **head)
{
	if (node == NULL)
		return ;
	free(node -> str);
	if (node == *head)
	{
		*head = node -> next;
	}
	else
	{
		if (node -> next != NULL)
			node -> next -> prev = node -> prev;
		node -> prev -> next = node -> next;
	}
	free (node);
	return ;
}

char	*make_str(int len, t_fd_list *node, t_fd_list **head, char *tmp)
{
	char	*str;

	str = (char *)malloc(len);
	if (str == NULL)
	{
		free_node(node, head);
		if (tmp != NULL)
			free(tmp);
		return (NULL);
	}
	str[len - 1] = '\0';
	return (str);
}
