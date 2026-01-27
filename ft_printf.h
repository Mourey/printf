/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmourey- <rmourey-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 12:07:22 by rmourey-          #+#    #+#             */
/*   Updated: 2026/01/27 12:21:05 by rmourey-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdarg.h>

typedef struct s_fmt
{
	int		minus;
	int		zero;
	int		hash;
	int		space;
	int		plus;
	int		width;
	int		precision;
	char	specifier;
}	t_fmt;

int		ft_printf(const char *format, ...);
int		ft_parse_format(const char *fmt, int *i, t_fmt *spec);
int		ft_print_char(char c, t_fmt *spec);
int		ft_print_str(char *s, t_fmt *spec);
int		ft_print_ptr(void *ptr, t_fmt *spec);
int		ft_print_nbr(int n, t_fmt *spec);
int		ft_print_unsigned(unsigned int n, t_fmt *spec);
int		ft_print_hex(unsigned int n, t_fmt *spec);
int		ft_putchar_count(char c);
int		ft_print_padding(int n, char c);

#endif
