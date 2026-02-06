/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmourey- <rmourey-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 12:30:00 by rmourey-          #+#    #+#             */
/*   Updated: 2026/02/04 11:38:24 by rmourey-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

int	ft_putchar_count(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_print_padding(int n, char c)
{
	int	count;

	count = 0;
	while (n > 0)
	{
		count += ft_putchar_count(c);
		n--;
	}
	return (count);
}
