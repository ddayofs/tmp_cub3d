/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee2 <donglee2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 16:08:56 by donglee2          #+#    #+#             */
/*   Updated: 2023/07/17 16:45:18 by donglee2         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	after_pct(const char *str, va_list ap)
{
	if (*str == 'c')
		return (ft_putchar(va_arg(ap, int)));
	else if (*str == 's')
		return (ft_putstr_fd_ret_cnt(va_arg(ap, char *), 1));
	else if (*str == 'p')
		return (ft_putnbr_base_addr(va_arg(ap,
					void *), "0123456789abcdef"));
	else if (*str == 'd' || *str == 'i')
		return (ft_putnbr_base_ll(va_arg(ap, int), "0123456789"));
	else if (*str == 'u')
		return (ft_putnbr_base_ll(va_arg(ap, unsigned int),
				"0123456789"));
	else if (*str == 'x')
		return (ft_putnbr_base_ll(va_arg(ap, unsigned int),
				"0123456789abcdef"));
	else if (*str == 'X')
		return (ft_putnbr_base_ll(va_arg(ap, unsigned int),
				"0123456789ABCDEF"));
	else if (*str == '%')
		return (write(1, "%%", 1));
	return (-1);
}

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	int		output_len;
	int		tmp;

	output_len = 0;
	va_start(ap, str);
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			tmp = after_pct(str, ap);
		}
		else
			tmp = write (1, str, 1);
		if (tmp == -1)
		{
			output_len = -1;
			break ;
		}
		output_len += tmp;
		str++;
	}
	va_end(ap);
	return (output_len);
}
