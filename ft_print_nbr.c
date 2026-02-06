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

static int	ft_print_digits(long n)
{
	int	count;

	count = 0;
	if (n >= 10)
		count += ft_print_digits(n / 10);
	count += ft_putchar_count('0' + (n % 10));
	return (count);
}

int	ft_print_nbr(int n)
{
	int		count;
	long	nb;

	count = 0;
	nb = n;
	if (nb < 0)
	{
		count += ft_putchar_count('-');
		nb = -nb;
	}
	count += ft_print_digits(nb);
	return (count);
}
