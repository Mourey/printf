/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmourey- <rmourey-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 12:30:00 by rmourey-          #+#    #+#             */
/*   Updated: 2026/01/27 12:30:00 by rmourey-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_dispatch(t_fmt *spec, va_list *args)
{
	int	count;

	count = 0;
	if (spec->specifier == 'c')
		count = ft_print_char((char)va_arg(*args, int), spec);
	else if (spec->specifier == 's')
		count = ft_print_str(va_arg(*args, char *), spec);
	else if (spec->specifier == 'p')
		count = ft_print_ptr(va_arg(*args, void *), spec);
	else if (spec->specifier == 'd' || spec->specifier == 'i')
		count = ft_print_nbr(va_arg(*args, int), spec);
	else if (spec->specifier == 'u')
		count = ft_print_unsigned(va_arg(*args, unsigned int), spec);
	else if (spec->specifier == 'x' || spec->specifier == 'X')
		count = ft_print_hex(va_arg(*args, unsigned int), spec);
	else if (spec->specifier == '%')
		count = ft_print_char('%', spec);
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		count;
	t_fmt	spec;

	if (!format)
		return (-1);
	va_start(args, format);
	i = 0;
	count = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			if (ft_parse_format(format, &i, &spec))
				count += ft_dispatch(&spec, &args);
		}
		else
			count += ft_putchar_count(format[i]);
		i++;
	}
	va_end(args);
	return (count);
}
