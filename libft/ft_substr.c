/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee2 <donglee2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 13:53:10 by donglee2          #+#    #+#             */
/*   Updated: 2023/09/05 11:09:50 by donglee2         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;
	size_t	s_len;
	size_t	i;

	s_len = ft_strlen(s);
	if (s_len <= start)
		return (ft_strdup(""));
	if (start + len > s_len)
		len = s_len - start;
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	ret[len] = '\0';
	i = 0;
	while (i < len)
	{
		ret[i] = s[start + i];
		i++;
	}
	return (ret);
}
