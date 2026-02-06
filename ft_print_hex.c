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

int	ft_print_hex(unsigned int n, char format)
{
	return (ft_print_hex_digits(n, format));
}
