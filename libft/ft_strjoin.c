/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee2 <donglee2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 17:56:16 by donglee2          #+#    #+#             */
/*   Updated: 2023/05/29 16:55:58 by donglee2         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	char	*tmp_ptr;
	int		sum_len;

	sum_len = ft_strlen(s1) + ft_strlen(s2);
	ret = (char *)malloc(sizeof(char) * (sum_len + 1));
	if (!ret)
		return (NULL);
	tmp_ptr = ret;
	while (*s1)
		*(tmp_ptr++) = *(s1++);
	while (*s2)
		*(tmp_ptr++) = *(s2++);
	*tmp_ptr = '\0';
	return (ret);
}
