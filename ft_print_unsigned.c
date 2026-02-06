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

int	ft_print_unsigned(unsigned int n)
{
	return (ft_print_udigits(n));
}
