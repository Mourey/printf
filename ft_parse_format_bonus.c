/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_format_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmourey- <rmourey-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 12:30:00 by rmourey-          #+#    #+#             */
/*   Updated: 2026/01/27 12:30:00 by rmourey-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static void	ft_init_spec(t_fmt *spec)
{
	spec->minus = 0;
	spec->zero = 0;
	spec->hash = 0;
	spec->space = 0;
	spec->plus = 0;
	spec->width = 0;
	spec->precision = -1;
	spec->specifier = 0;
}

static void	ft_parse_flags(const char *fmt, int *i, t_fmt *spec)
{
	while (fmt[*i] && ft_strchr("-0# +", fmt[*i]))
	{
		if (fmt[*i] == '-')
			spec->minus = 1;
		else if (fmt[*i] == '0')
			spec->zero = 1;
		else if (fmt[*i] == '#')
			spec->hash = 1;
		else if (fmt[*i] == ' ')
			spec->space = 1;
		else if (fmt[*i] == '+')
			spec->plus = 1;
		(*i)++;
	}
}

static void	ft_parse_width(const char *fmt, int *i, t_fmt *spec)
{
	while (fmt[*i] && ft_isdigit(fmt[*i]))
	{
		spec->width = spec->width * 10 + (fmt[*i] - '0');
		(*i)++;
	}
}

static void	ft_parse_precision(const char *fmt, int *i, t_fmt *spec)
{
	if (fmt[*i] == '.')
	{
		(*i)++;
		spec->precision = 0;
		while (fmt[*i] && ft_isdigit(fmt[*i]))
		{
			spec->precision = spec->precision * 10 + (fmt[*i] - '0');
			(*i)++;
		}
	}
}

int	ft_parse_format(const char *fmt, int *i, t_fmt *spec)
{
	ft_init_spec(spec);
	(*i)++;
	ft_parse_flags(fmt, i, spec);
	ft_parse_width(fmt, i, spec);
	ft_parse_precision(fmt, i, spec);
	if (fmt[*i] && ft_strchr("cspdiuxX%", fmt[*i]))
	{
		spec->specifier = fmt[*i];
		return (1);
	}
	return (0);
}
