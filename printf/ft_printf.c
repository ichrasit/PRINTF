/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhaoz <muhaoz@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 15:34:32 by muhaoz            #+#    #+#             */
/*   Updated: 2026/05/12 15:49:09 by muhaoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	cheat_putstr(char *s)
{
	int	i;

	if (!s)
		return (write(1, "(null)", 6));
	i = 0;
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
	return (i);
}

static int	cheat_hex_magic(unsigned long n, char *b, unsigned int blen)
{
	int	len;

	len = 0;
	if (n >= blen)
		len += cheat_hex_magic(n / blen, b, blen);
	len += write(1, &b[n % blen], 1);
	return (len);
}

static int	cheat_number_spit(int n)
{
	int		len;
	long	num;

	len = 0;
	num = n;
	if (num < 0)
	{
		len += write(1, "-", 1);
		num = -num;
	}
	len += cheat_hex_magic(num, "0123456789", 10);
	return (len);
}

static int	cheat_summon(char t, va_list ap)
{
	char	c;

	if (t == 'c')
	{
		c = (char)va_arg(ap, int);
		return (write(1, &c, 1));
	}
	if (t == 's')
		return (cheat_putstr(va_arg(ap, char *)));
	if (t == 'p')
		return (write(1, "0x", 2) + cheat_hex_magic(
				(unsigned long)va_arg(ap, void *), "0123456789abcdef", 16));
	if (t == 'd' || t == 'i')
		return (cheat_number_spit(va_arg(ap, int)));
	if (t == 'u')
		return (cheat_hex_magic(va_arg(ap, unsigned int), "0123456789", 10));
	if (t == 'x')
		return (cheat_hex_magic(va_arg(ap, unsigned int),
				"0123456789abcdef", 16));
	if (t == 'X')
		return (cheat_hex_magic(va_arg(ap, unsigned int),
				"0123456789ABCDEF", 16));
	if (t == '%')
		return (write(1, "%", 1));
	return (0);
}

int	ft_printf(const char *s, ...)
{
	va_list	ap;
	int		i;
	int		len;

	if (!s)
		return (-1);
	va_start(ap, s);
	i = 0;
	len = 0;
	while (s[i])
	{
		if (s[i] == '%')
		{
			if (!s[i + 1])
			{
				len = -1;
				break ;
			}
			len += cheat_summon(s[i + 1], ap);
			i++;
		}
		else
			len += write(1, &s[i], 1);
		i++;
	}
	va_end(ap);
	return (len);
}

