/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmourey- <rmourey-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 12:30:00 by rmourey-          #+#    #+#             */
/*   Updated: 2026/01/27 12:30:00 by rmourey-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static int	ft_print_hex_digits(unsigned int n, char format)
{
	int		count;
	char	*hex;

	count = 0;
	if (format == 'X')
		hex = "0123456789ABCDEF";
	else
		hex = "0123456789abcdef";
	if (n >= 16)
		count += ft_print_hex_digits(n / 16, format);
	count += ft_putchar_count(hex[n % 16]);
	return (count);
}

static int	ft_hex_len(unsigned int n, int prec_zero)
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
		n /= 16;
	}
	return (len);
}

static int	ft_write_hex(unsigned int n, t_fmt *sp, int prec_pad, int dlen)
{
	int	c;

	c = 0;
	if (sp->hash && n != 0)
	{
		c += ft_putchar_count('0');
		c += ft_putchar_count(sp->specifier);
	}
	c += ft_print_padding(prec_pad, '0');
	if (dlen > 0)
		c += ft_print_hex_digits(n, sp->specifier);
	return (c);
}

static int	ft_hex_out(unsigned int n, t_fmt *sp, int *l)
{
	int	c;
	int	plen;

	plen = 0;
	if (sp->hash && n != 0)
		plen = 2;
	if (sp->minus)
	{
		c = ft_write_hex(n, sp, l[1] - l[0], l[0]);
		return (c + ft_print_padding(sp->width - l[1] - plen, ' '));
	}
	if (sp->zero && sp->precision < 0)
	{
		c = ft_write_hex(n, sp, sp->width - l[1] - plen + l[1] - l[0], l[0]);
		return (c);
	}
	c = ft_print_padding(sp->width - l[1] - plen, ' ');
	return (c + ft_write_hex(n, sp, l[1] - l[0], l[0]));
}

int	ft_print_hex(unsigned int n, t_fmt *spec)
{
	int	l[2];

	l[0] = ft_hex_len(n, n == 0 && spec->precision == 0);
	l[1] = l[0];
	if (spec->precision > l[0])
		l[1] = spec->precision;
	return (ft_hex_out(n, spec, l));
}
