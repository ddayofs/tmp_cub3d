/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgu <hgu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 18:32:26 by hgu               #+#    #+#             */
/*   Updated: 2023/05/12 16:50:03 by hgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	decimal_to_hex(unsigned long long ap)
{
	int	tmp;

	if (ap >= 16)
	{
		tmp = decimal_to_hex(ap / 16);
		if (tmp == -1)
			return (-1);
		if (write(1, &"0123456789abcdef"[ap % 16], 1) == -1)
			return (-1);
	}
	else
	{
		if (write(1, &"0123456789abcdef"[ap % 16], 1) == -1)
			return (-1);
		tmp = 1;
	}
	return (tmp + 1);
}

int	decimal_to_big(unsigned long long ap)
{
	int	tmp;

	if (ap >= 16)
	{
		tmp = decimal_to_big(ap / 16);
		if (tmp == -1)
			return (-1);
		if (write(1, &"0123456789ABCDEF"[ap % 16], 1) == -1)
			return (-1);
	}
	else
	{
		if (write(1, &"0123456789ABCDEF"[ap % 16], 1) == -1)
			return (-1);
		tmp = 1;
	}
	if (tmp == -1)
		return (-1);
	return (tmp + 1);
}

int	ft_print_hex(unsigned int ap)
{
	int	tmp;

	tmp = decimal_to_hex((unsigned long long)ap);
	if (tmp == -1)
		return (-1);
	return (tmp - 1);
}

int	ft_print_big(unsigned int ap)
{
	int	tmp;

	tmp = decimal_to_big((unsigned long long)ap);
	if (tmp == -1)
		return (-1);
	return (tmp - 1);
}

int	ft_print_addr(unsigned long long ap)
{
	unsigned long long	addr;
	int					tmp;

	addr = (unsigned long long)ap;
	tmp = write (1, &"0x", 2);
	if (tmp == -1)
		return (-1);
	tmp += decimal_to_hex(addr);
	if (tmp == 1)
		return (-1);
	return (tmp - 1);
}
