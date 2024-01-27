/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee2 <donglee2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:28:56 by donglee2          #+#    #+#             */
/*   Updated: 2023/09/05 12:26:08 by donglee2         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char				*tmp_dst;
	const unsigned char	*tmp_src;

	if (dst == src)
		return (NULL);
	tmp_dst = dst;
	tmp_src = src;
	while (n--)
		*(tmp_dst++) = *(tmp_src++);
	return (dst);
}
