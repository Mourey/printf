/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmourey- <rmourey-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 12:30:00 by rmourey-          #+#    #+#             */
/*   Updated: 2026/01/27 12:30:00 by rmourey-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_num_len(long n)
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

static int	ft_print_digits(long n)
{
	int	count;

	count = 0;
	if (n >= 10)
		count += ft_print_digits(n / 10);
	count += ft_putchar_count('0' + (n % 10));
	return (count);
}

static int	ft_get_sign_char(int is_neg, t_fmt *spec)
{
	if (is_neg)
		return ('-');
	if (spec->plus)
		return ('+');
	if (spec->space)
		return (' ');
	return (0);
}

static void	ft_calc_lens(long nb, t_fmt *spec, int *lens)
{
	int	digit_len;
	int	num_len;

	digit_len = ft_num_len(nb);
	if (nb == 0 && spec->precision == 0)
		digit_len = 0;
	num_len = digit_len;
	if (spec->precision > digit_len)
		num_len = spec->precision;
	lens[0] = digit_len;
	lens[1] = num_len;
}

int	ft_print_nbr(int n, t_fmt *spec)
{
	int		count;
	int		lens[2];
	long	nb;
	int		sign;
	int		total_len;
	char	pad;

	count = 0;
	nb = n;
	sign = ft_get_sign_char(nb < 0, spec);
	if (nb < 0)
		nb = -nb;
	ft_calc_lens(nb, spec, lens);
	total_len = lens[1] + (sign != 0);
	pad = ' ';
	if (spec->zero && !spec->minus && spec->precision < 0)
		pad = '0';
	if (spec->minus)
	{
		if (sign)
			count += ft_putchar_count(sign);
		count += ft_print_padding(lens[1] - lens[0], '0');
		if (!(nb == 0 && spec->precision == 0))
			count += ft_print_digits(nb);
		count += ft_print_padding(spec->width - total_len, ' ');
	}
	else if (pad == '0')
	{
		if (sign)
			count += ft_putchar_count(sign);
		count += ft_print_padding(spec->width - total_len, '0');
		if (!(nb == 0 && spec->precision == 0))
			count += ft_print_digits(nb);
	}
	else
	{
		count += ft_print_padding(spec->width - total_len, ' ');
		if (sign)
			count += ft_putchar_count(sign);
		count += ft_print_padding(lens[1] - lens[0], '0');
		if (!(nb == 0 && spec->precision == 0))
			count += ft_print_digits(nb);
	}
	return (count);
}
