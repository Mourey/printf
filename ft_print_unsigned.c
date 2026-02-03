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

static int	ft_print_udigits(unsigned int n)
{
	int	count;

	count = 0;
	if (n >= 10)
		count += ft_print_udigits(n / 10);
	count += ft_putchar_count('0' + (n % 10));
	return (count);
}

static int	ft_unum_len(unsigned int n, int prec_zero)
{
	int	len;

	if (prec_zero)
		return (0);
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

static int	ft_write_unum(unsigned int n, int prec_pad, int digit_len)
{
	int	count;

	count = ft_print_padding(prec_pad, '0');
	if (digit_len > 0)
		count += ft_print_udigits(n);
	return (count);
}

static int	ft_unum_out(unsigned int n, t_fmt *sp, int *l)
{
	int	c;

	if (sp->minus)
	{
		c = ft_write_unum(n, l[1] - l[0], l[0]);
		return (c + ft_print_padding(sp->width - l[1], ' '));
	}
	if (sp->zero && sp->precision < 0)
	{
		c = ft_print_padding(sp->width - l[1], '0');
		return (c + ft_write_unum(n, l[1] - l[0], l[0]));
	}
	c = ft_print_padding(sp->width - l[1], ' ');
	return (c + ft_write_unum(n, l[1] - l[0], l[0]));
}

int	ft_print_unsigned(unsigned int n, t_fmt *spec)
{
	int	l[2];

	l[0] = ft_unum_len(n, n == 0 && spec->precision == 0);
	l[1] = l[0];
	if (spec->precision > l[0])
		l[1] = spec->precision;
	return (ft_unum_out(n, spec, l));
}
