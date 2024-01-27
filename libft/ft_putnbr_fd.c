/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee2 <donglee2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 19:44:01 by donglee2          #+#    #+#             */
/*   Updated: 2023/07/12 18:12:48 by donglee2         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	how_many_digits_2(long long nbr)
{
	int	cnt;

	cnt = 1;
	while (nbr > 9)
	{
		nbr /= 10;
		cnt++;
	}
	return (cnt);
}

void	ft_putnbr_fd(int n, int fd)
{
	long long	nbr;
	int			nbr_len;
	char		arr[12];
	int			i;

	nbr = (long long)n;
	if (nbr < 0)
	{
		write(fd, "-", 1);
		nbr *= -1;
	}
	nbr_len = how_many_digits_2(nbr);
	arr[nbr_len] = 0;
	while (nbr_len--)
	{
		arr[nbr_len] = (nbr % 10) + '0';
		nbr /= 10;
	}
	i = -1;
	while (arr[++i])
		write(fd, &arr[i], 1);
}
