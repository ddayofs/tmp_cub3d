/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee2 <donglee2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 09:54:41 by donglee2          #+#    #+#             */
/*   Updated: 2023/05/29 16:27:44 by donglee2         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*ptr;
	char	ch;

	ch = (char)c;
	ptr = (char *)s;
	while (*ptr)
	{
		if (*ptr == ch)
			return (ptr);
		ptr++;
	}
	if (ch == '\0')
		return (ptr);
	return (0);
}
