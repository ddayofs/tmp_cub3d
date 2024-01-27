/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgu <hgu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 18:15:41 by hgu               #+#    #+#             */
/*   Updated: 2023/09/11 18:47:25 by hgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "ft_printf.h"
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct fd_list
{
	int				fd;
	int				len;
	char			*str;
	struct fd_list	*prev;
	struct fd_list	*next;
}	t_fd_list;

char		*get_next_line(int fd);
char		*read_value(int fd, t_fd_list *node, t_fd_list **head);
int			find_nl(t_fd_list *node, int read_size);
void		free_node(t_fd_list *node, t_fd_list **head);
t_fd_list	*malloc_node(int fd, t_fd_list *prev);
int			ft_strlen(char *s);
char		*ft_strjoin(char *s1, char *s2, int read_size);
char		*ft_nl(char *str, t_fd_list *node, t_fd_list **head);
char		*ft_end(char *str, t_fd_list *node, t_fd_list **head);
char		*make_str(int len, t_fd_list *node, t_fd_list **head, char *tmp);
void		ft_error(char *str);
#endif