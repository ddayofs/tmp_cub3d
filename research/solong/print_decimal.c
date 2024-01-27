/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_decimal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgu <hgu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 18:45:12 by hgu               #+#    #+#             */
/*   Updated: 2023/05/09 19:37:08 by hgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	minus_to_plus(int ap, int *len)
{
	if (ap < 0)
	{
		ap *= -1;
		*len += 1;
		if (write(1, &"-", 1) == -1)
			return (-1);
	}
	return (ap);
}

void	nbr_value_change(int *digit, int *ap, int *len)
{
	*ap %= *digit;
	*digit /= 10;
	*len += 1;
}

void	unbr_value_change(int *digit, unsigned int *ap, int *len)
{
	*ap %= *digit;
	*digit /= 10;
	*len += 1;
}

int	ft_print_nbr(int ap)
{
	int		digit;
	char	tmp;
	int		len;

	digit = 1;
	len = 0;
	if (ap == -2147483648)
	{
		if (write(1, "-2147483648", 11) == -1)
			return (-1);
		return (11);
	}
	ap = minus_to_plus(ap, &len);
	while ((ap / digit) >= 10)
		digit *= 10;
	if (ap == -1)
		return (-1);
	while (digit)
	{
		tmp = ap / digit + 48;
		if (write (1, &tmp, 1) == -1)
			return (-1);
		nbr_value_change(&digit, &ap, &len);
	}
	return (len);
}

int	ft_print_unbr(unsigned int ap)
{
	int		digit;
	char	tmp;
	int		len;

	digit = 1;
	len = 0;
	while ((ap / digit) >= 10)
		digit *= 10;
	while (digit)
	{
		tmp = ap / digit + 48;
		if (write (1, &tmp, 1) == -1)
			return (-1);
		unbr_value_change(&digit, &ap, &len);
	}
	return (len);
}
