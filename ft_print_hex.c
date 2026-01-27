/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmourey- <rmourey-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 12:30:00 by rmourey-          #+#    #+#             */
/*   Updated: 2026/01/27 12:30:00 by rmourey-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_hex_len(unsigned int n)
{
	int	len;

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

static int	ft_print_prefix(char format)
{
	int	count;

	count = 0;
	count += ft_putchar_count('0');
	if (format == 'X')
		count += ft_putchar_count('X');
	else
		count += ft_putchar_count('x');
	return (count);
}

static void	ft_calc_hex_lens(unsigned int n, t_fmt *spec, int *lens)
{
	int	digit_len;
	int	num_len;
	int	prefix_len;
	int	total_len;

	digit_len = ft_hex_len(n);
	if (n == 0 && spec->precision == 0)
		digit_len = 0;
	num_len = digit_len;
	if (spec->precision > digit_len)
		num_len = spec->precision;
	prefix_len = 0;
	if (spec->hash && n != 0)
		prefix_len = 2;
	total_len = num_len + prefix_len;
	lens[0] = digit_len;
	lens[1] = num_len;
	lens[2] = prefix_len;
	lens[3] = total_len;
}

int	ft_print_hex(unsigned int n, t_fmt *spec)
{
	int		count;
	int		lens[4];
	char	pad;

	count = 0;
	ft_calc_hex_lens(n, spec, lens);
	pad = ' ';
	if (spec->zero && !spec->minus && spec->precision < 0)
		pad = '0';
	if (spec->minus)
	{
		if (lens[2])
			count += ft_print_prefix(spec->specifier);
		count += ft_print_padding(lens[1] - lens[0], '0');
		if (!(n == 0 && spec->precision == 0))
			count += ft_print_hex_digits(n, spec->specifier);
		count += ft_print_padding(spec->width - lens[3], ' ');
	}
	else if (pad == '0')
	{
		if (lens[2])
			count += ft_print_prefix(spec->specifier);
		count += ft_print_padding(spec->width - lens[3], '0');
		count += ft_print_padding(lens[1] - lens[0], '0');
		if (!(n == 0 && spec->precision == 0))
			count += ft_print_hex_digits(n, spec->specifier);
	}
	else
	{
		count += ft_print_padding(spec->width - lens[3], ' ');
		if (lens[2])
			count += ft_print_prefix(spec->specifier);
		count += ft_print_padding(lens[1] - lens[0], '0');
		if (!(n == 0 && spec->precision == 0))
			count += ft_print_hex_digits(n, spec->specifier);
	}
	return (count);
}
