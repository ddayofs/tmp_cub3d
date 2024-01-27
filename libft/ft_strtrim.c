/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee2 <donglee2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 18:15:30 by donglee2          #+#    #+#             */
/*   Updated: 2023/03/24 11:07:13 by donglee2         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in_set(char c, char const *set)
{
	int	k;

	k = 0;
	while (set[k])
	{
		if (c == set[k])
			return (1);
		k++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ret_ptr;
	int		s1_len;
	int		ret_ptr_len;
	int		start;
	int		j;

	start = -1;
	s1_len = ft_strlen(s1);
	while (is_in_set(s1[++start], set))
		;
	if (start == s1_len)
		return (ft_strdup(""));
	while (is_in_set(s1[--s1_len], set))
		;
	ret_ptr_len = s1_len - start + 1;
	ret_ptr = (char *)malloc(sizeof(char) * (ret_ptr_len + 1));
	if (ret_ptr == 0)
		return (0);
	j = -1;
	while (++j < ret_ptr_len)
		ret_ptr[j] = s1[start++];
	ret_ptr[j] = 0;
	return (ret_ptr);
}
