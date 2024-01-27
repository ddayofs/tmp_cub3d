/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgu <hgu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 20:36:14 by hgu               #+#    #+#             */
/*   Updated: 2023/05/09 19:37:41 by hgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_char(int ap)
{
	if (write (1, &ap, 1) == -1)
		return (-1);
	return (1);
}

int	ft_print_str(const char *ap)
{
	int	idx;

	idx = 0;
	if (ap == NULL)
		return (write (1, "(null)", 6));
	while (ap[idx])
		idx++;
	if (write(1, (char *)ap, idx) == -1)
		return (-1);
	return (idx);
}

int	ft_function(const char *str, va_list ap)
{
	int	tmp;

	tmp = 0;
	if (*str == 'c')
		tmp = ft_print_char(va_arg(ap, int));
	else if (*str == 'd' || *str == 'i')
		tmp = ft_print_nbr(va_arg(ap, int));
	else if (*str == 'u')
		tmp = ft_print_unbr(va_arg(ap, unsigned int));
	else if (*str == 's')
		tmp = ft_print_str(va_arg(ap, const char *));
	else if (*str == '%')
		tmp = write(1, &"%", 1);
	else if (*str == 'x')
		tmp = ft_print_hex(va_arg(ap, int));
	else if (*str == 'X')
		tmp = ft_print_big(va_arg(ap, int));
	else if (*str == 'p')
		tmp = ft_print_addr(va_arg(ap, unsigned long long));
	return (tmp);
}

int	ft_printf(const char *str, ...)
{
	int		len;
	int		tmp;
	va_list	ap;

	len = 0;
	va_start(ap, str);
	while (*str)
	{
		if (*str == '%')
		{
			tmp = ft_function(++str, ap);
			if (tmp == -1)
				return (-1);
		}
		else
			tmp = write(1, str, 1);
		if (tmp == -1)
			return (-1);
		len += tmp;
		str++;
	}
	return (len);
}
