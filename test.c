/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmourey- <rmourey-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 11:32:16 by rmourey-          #+#    #+#             */
/*   Updated: 2026/02/04 11:35:53 by rmourey-         ###   ########.fr       */
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
