/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmourey- <rmourey-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 12:30:00 by rmourey-          #+#    #+#             */
/*   Updated: 2026/01/27 12:30:00 by rmourey-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_print_str_content(char *s, int len)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (i < len)
	{
		count += ft_putchar_count(s[i]);
		i++;
	}
	return (count);
}

int	ft_print_str(char *s, t_fmt *spec)
{
	int	count;
	int	len;
	int	print_len;

	count = 0;
	if (!s)
		s = "(null)";
	len = ft_strlen(s);
	print_len = len;
	if (spec->precision >= 0 && spec->precision < len)
		print_len = spec->precision;
	if (spec->minus)
	{
		count += ft_print_str_content(s, print_len);
		count += ft_print_padding(spec->width - print_len, ' ');
	}
	else
	{
		count += ft_print_padding(spec->width - print_len, ' ');
		count += ft_print_str_content(s, print_len);
	}
	return (count);
}
