/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee2 <donglee2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 18:04:18 by donglee2          #+#    #+#             */
/*   Updated: 2023/07/12 18:24:07 by donglee2         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t	ft_strchr_idx(char *s, int c)
{
	ssize_t		idx;
	char		ch;

	idx = 0;
	ch = (char)c;
	while (s[idx])
	{
		if (s[idx] == ch)
			return (idx);
		idx++;
	}
	if (ch == '\0')
		return (idx);
	return (-1);
}
