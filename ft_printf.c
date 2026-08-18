/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhaoz <muhaoz@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 02:11:51 by muhaoz            #+#    #+#             */
/*   Updated: 2026/08/19 02:14:09 by muhaoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	init_table(t_fmt_func *t)
{
	int	i;

	i = 0;
	while (i < 256)
	{
		t[i] = NULL;
		i++;
	}
	t['c'] = handle_c;
	t['s'] = handle_s;
	t['%'] = handle_pct;
	t['d'] = handle_d;
	t['i'] = handle_d;
	t['u'] = handle_u;
	t['x'] = handle_x_low;
	t['X'] = handle_x_up;
	t['p'] = handle_p;
}

static int	process_format(const char **f, va_list args, t_fmt_func *t)
{
	int	len;

	(*f)++;
	if (!**f)
		return (-1);
	if (t[(unsigned char)**f])
		len = t[(unsigned char)**f](args);
	else
		len = write(1, *f, 1);
	(*f)++;
	return (len);
}

static int	print_all(const char *f, va_list args, t_fmt_func *t)
{
	int	total;
	int	tmp;

	total = 0;
	while (*f)
	{
		if (*f != '%')
			total += write(1, f++, 1);
		else
		{
			tmp = process_format(&f, args, t);
			if (tmp == -1)
				return (-1);
			total += tmp;
		}
	}
	return (total);
}

int	ft_printf(const char *format, ...)
{
	va_list		args;
	int			total;
	t_fmt_func	t[256];

	if (!format)
		return (-1);
	init_table(t);
	va_start(args, format);
	total = print_all(format, args, t);
	va_end(args);
	return (total);
}
