/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee2 <donglee2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 19:14:53 by donglee2          #+#    #+#             */
/*   Updated: 2023/03/24 11:12:10 by donglee2         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*tmp_dst;
	const unsigned char	*tmp_src;
	size_t				i;

	tmp_dst = (unsigned char *)dst;
	tmp_src = (const unsigned char *)src;
	if (dst == src || len == 0)
		return (dst);
	else if (dst > src)
	{
		i = len;
		while (i--)
			*(tmp_dst + i) = *(tmp_src + i);
	}
	else
	{
		i = -1;
		while (++i < len)
			*(tmp_dst + i) = *(tmp_src + i);
	}
	return (dst);
}
