/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmourey- <rmourey-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 12:30:00 by rmourey-          #+#    #+#             */
/*   Updated: 2026/01/27 12:30:00 by rmourey-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_unum_len(unsigned int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

static int	ft_print_udigits(unsigned int n)
{
	int	count;

	count = 0;
	if (n >= 10)
		count += ft_print_udigits(n / 10);
	count += ft_putchar_count('0' + (n % 10));
	return (count);
}

int	ft_print_unsigned(unsigned int n, t_fmt *spec)
{
	int		count;
	int		digit_len;
	int		num_len;
	int		total_len;
	char	pad;

	count = 0;
	digit_len = ft_unum_len(n);
	if (n == 0 && spec->precision == 0)
		digit_len = 0;
	num_len = digit_len;
	if (spec->precision > digit_len)
		num_len = spec->precision;
	total_len = num_len;
	pad = ' ';
	if (spec->zero && !spec->minus && spec->precision < 0)
		pad = '0';
	if (spec->minus)
	{
		count += ft_print_padding(num_len - digit_len, '0');
		if (!(n == 0 && spec->precision == 0))
			count += ft_print_udigits(n);
		count += ft_print_padding(spec->width - total_len, ' ');
	}
	else if (pad == '0')
	{
		count += ft_print_padding(spec->width - total_len, '0');
		count += ft_print_padding(num_len - digit_len, '0');
		if (!(n == 0 && spec->precision == 0))
			count += ft_print_udigits(n);
	}
	else
	{
		count += ft_print_padding(spec->width - total_len, ' ');
		count += ft_print_padding(num_len - digit_len, '0');
		if (!(n == 0 && spec->precision == 0))
			count += ft_print_udigits(n);
	}
	return (count);
}
