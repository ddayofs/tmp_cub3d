/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee2 <donglee2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 13:25:35 by donglee2          #+#    #+#             */
/*   Updated: 2023/07/12 18:25:35 by donglee2         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*return_arr;
	int		src_len;
	int		i;

	i = 0;
	src_len = ft_strlen(src);
	return_arr = (char *)malloc(sizeof(char) * (src_len + 1));
	if (!return_arr)
		return (0);
	while (src[i])
	{
		return_arr[i] = src[i];
		i++;
	}
	return_arr[i] = 0;
	return (return_arr);
}
