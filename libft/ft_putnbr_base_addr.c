/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_addr.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee2 <donglee2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 20:40:43 by donglee2          #+#    #+#             */
/*   Updated: 2023/07/17 16:47:05 by donglee2         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	base_check(char *base)
{
	int	base_len;
	int	i;
	int	j;

	i = 0;
	base_len = ft_strlen(base);
	while (base[i])
	{
		if (base[i] == '+' || base[i] == '-')
			return (-1);
		j = i + 1;
		while (base[j])
		{
			if (base[i] == base[j])
				return (-1);
			j++;
		}
		i++;
	}
	return (base_len);
}

static int	bytes_needed(unsigned long long nbr, int base_len)
{
	int	cnt;

	cnt = 0;
	if (nbr == 0)
		cnt++;
	if (nbr < 0)
	{
		cnt++;
		nbr *= -1;
	}
	while (nbr)
	{
		nbr /= base_len;
		cnt++;
	}
	cnt += 1;
	return (cnt);
}

static int	int_to_str(unsigned long long nbr, char *str,
	char *base, int base_len)
{
	int	null_idx;
	int	tmp_idx;

	null_idx = bytes_needed(nbr, base_len) - 1;
	tmp_idx = null_idx;
	str[tmp_idx] = 0;
	tmp_idx--;
	if (nbr == 0)
		str[0] = '0';
	if (nbr < 0)
	{
		str[0] = '-';
		nbr *= -1;
	}
	while (nbr)
	{
		str[tmp_idx] = base[nbr % base_len];
		nbr /= base_len;
		tmp_idx--;
	}
	return (null_idx);
}

int	ft_putnbr_base_addr(void *addr, char *base)
{
	char				str[100];
	int					idx;
	unsigned long long	nbr;

	nbr = (unsigned long long)addr;
	if (base_check(base) < 2)
		return (0);
	int_to_str(nbr, str, base, base_check(base));
	if (write(1, "0x", 2) == -1)
		return (-1);
	idx = 0;
	while (str[idx])
	{
		if (write(1, &str[idx], 1) == -1)
			return (-1);
		idx++;
	}
	return (idx + 2);
}
