/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmourey- <rmourey-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 12:30:00 by rmourey-          #+#    #+#             */
/*   Updated: 2026/01/27 12:30:00 by rmourey-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static int	ft_ptr_len(unsigned long n)
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

static int	ft_print_ptr_hex(unsigned long n)
{
	int		count;
	char	*hex;

	count = 0;
	hex = "0123456789abcdef";
	if (n >= 16)
		count += ft_print_ptr_hex(n / 16);
	count += ft_putchar_count(hex[n % 16]);
	return (count);
}

int	ft_print_ptr(void *ptr, t_fmt *spec)
{
	int				count;
	int				total_len;
	unsigned long	addr;

	count = 0;
	addr = (unsigned long)ptr;
	total_len = ft_ptr_len(addr) + 2;
	if (spec->minus)
	{
		count += ft_putchar_count('0');
		count += ft_putchar_count('x');
		count += ft_print_ptr_hex(addr);
		count += ft_print_padding(spec->width - total_len, ' ');
	}
	else
	{
		count += ft_print_padding(spec->width - total_len, ' ');
		count += ft_putchar_count('0');
		count += ft_putchar_count('x');
		count += ft_print_ptr_hex(addr);
	}
	return (count);
}
