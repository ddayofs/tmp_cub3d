/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd_ret_cnt.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee2 <donglee2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 10:52:39 by donglee2          #+#    #+#             */
/*   Updated: 2023/07/17 16:46:12 by donglee2         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr_fd_ret_cnt(char *s, int fd)
{
	int	i;

	i = -1;
	if (s == NULL)
		return (write(fd, "(null)", 6));
	while (s[++i])
	{
		if (write(fd, &s[i], 1) == -1)
			return (-1);
	}
	return (i);
}
