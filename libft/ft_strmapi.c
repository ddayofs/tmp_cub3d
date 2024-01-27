/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee2 <donglee2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 14:04:01 by donglee2          #+#    #+#             */
/*   Updated: 2023/03/24 11:36:19 by donglee2         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*ret_ptr;
	int		s_len;
	int		i;

	s_len = ft_strlen(s);
	ret_ptr = (char *)malloc(sizeof(char) * (s_len + 1));
	if (ret_ptr == 0)
		return (0);
	i = 0;
	while (s[i])
	{
		ret_ptr[i] = f(i, s[i]);
		i++;
	}
	ret_ptr[i] = 0;
	return (ret_ptr);
}
