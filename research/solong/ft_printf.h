/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgu <hgu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 20:32:03 by hgu               #+#    #+#             */
/*   Updated: 2023/09/11 18:47:27 by hgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>

int		ft_print_char(int ap);
int		ft_print_str(const char *ap);
int		ft_function(const char *str, va_list ap);
int		ft_printf(const char *str, ...);
int		minus_to_plus(int ap, int *len);
void	nbr_value_change(int *digit, int *ap, int *len);
void	unbr_value_change(int *digit, unsigned int *ap, int *len);
int		ft_print_nbr(int ap);
int		ft_print_unbr(unsigned int ap);
int		decimal_to_hex(unsigned long long ap);
int		decimal_to_big(unsigned long long ap);
int		ft_print_hex(unsigned int ap);
int		ft_print_big(unsigned int ap);
int		ft_print_addr(unsigned long long ap);
#endif