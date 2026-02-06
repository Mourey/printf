/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nbr_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmourey- <rmourey-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 12:30:00 by rmourey-          #+#    #+#             */
/*   Updated: 2026/01/27 12:30:00 by rmourey-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static int	ft_print_digits(long n)
{
	int	count;

	count = 0;
	if (n >= 10)
		count += ft_print_digits(n / 10);
	count += ft_putchar_count('0' + (n % 10));
	return (count);
}

static int	ft_num_len(long n, int prec_zero)
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

static int	ft_write_num(long nb, int sign, int prec_pad, int digit_len)
{
	int	count;

	count = 0;
	if (sign)
		count += ft_putchar_count(sign);
	count += ft_print_padding(prec_pad, '0');
	if (digit_len > 0)
		count += ft_print_digits(nb);
	return (count);
}

static int	ft_nbr_out(long nb, t_fmt *sp, int sign, int *l)
{
	int	c;

	if (sp->minus)
	{
		c = ft_write_num(nb, sign, l[1] - l[0], l[0]);
		return (c + ft_print_padding(sp->width - l[2], ' '));
	}
	if (sp->zero && sp->precision < 0)
	{
		c = 0;
		if (sign)
			c = ft_putchar_count(sign);
		c += ft_print_padding(sp->width - l[2], '0');
		if (l[0] > 0)
			c += ft_print_digits(nb);
		return (c);
	}
	c = ft_print_padding(sp->width - l[2], ' ');
	return (c + ft_write_num(nb, sign, l[1] - l[0], l[0]));
}

int	ft_print_nbr(int n, t_fmt *spec)
{
	int		l[3];
	long	nb;
	int		sign;

	nb = n;
	sign = 0;
	if (nb < 0)
	{
		sign = '-';
		nb = -nb;
	}
	else if (spec->plus)
		sign = '+';
	else if (spec->space)
		sign = ' ';
	l[0] = ft_num_len(nb, nb == 0 && spec->precision == 0);
	l[1] = l[0];
	if (spec->precision > l[0])
		l[1] = spec->precision;
	l[2] = l[1] + (sign != 0);
	return (ft_nbr_out(nb, spec, sign, l));
}
