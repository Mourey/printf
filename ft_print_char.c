/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmourey- <rmourey-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 12:30:00 by rmourey-          #+#    #+#             */
/*   Updated: 2026/01/27 12:30:00 by rmourey-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_char(char c, t_fmt *spec)
{
	int	count;

	count = 0;
	if (spec->minus)
	{
		count += ft_putchar_count(c);
		count += ft_print_padding(spec->width - 1, ' ');
	}
	else
	{
		count += ft_print_padding(spec->width - 1, ' ');
		count += ft_putchar_count(c);
	}
	return (count);
}
