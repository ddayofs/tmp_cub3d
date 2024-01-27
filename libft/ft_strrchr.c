/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee2 <donglee2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 10:21:30 by donglee2          #+#    #+#             */
/*   Updated: 2023/03/24 11:07:07 by donglee2         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ptr;

	ptr = (char *)s;
	while (*ptr)
		ptr++;
	while (1)
	{
		if (ptr == (char *)s)
			break ;
		if (*ptr == (char)c)
			return (ptr);
		ptr--;
	}
	if (*ptr == (char)c)
		return (ptr);
	return (0);
}
