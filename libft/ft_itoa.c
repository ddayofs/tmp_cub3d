/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee2 <donglee2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 13:04:53 by donglee2          #+#    #+#             */
/*   Updated: 2023/06/05 14:47:04 by donglee2         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	how_many_digits_1(long long nbr, int base_len)
{
	int	count;

	count = 0;
	if (nbr == 0)
		count++;
	else if (nbr < 0)
	{
		count++;
		nbr *= -1;
	}
	while (nbr > 0)
	{
		nbr /= base_len;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	long long	nbr;
	char		*ret;
	int			ret_len;
	int			i;

	nbr = (long long)n;
	ret_len = how_many_digits_1(nbr, 10);
	ret = (char *)malloc(sizeof(char) * (ret_len + 1));
	if (ret == 0)
		return (0);
	if (nbr == 0)
		ret[0] = '0';
	else if (nbr < 0)
	{
		nbr *= -1;
		ret[0] = '-';
	}
	i = 0;
	while (nbr > 0)
	{
		ret[ret_len - 1 - i++] = nbr % 10 + '0';
		nbr /= 10;
	}
	ret[ret_len] = 0;
	return (ret);
}
