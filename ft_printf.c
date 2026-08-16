/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhaoz <muhaoz@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 15:34:32 by muhaoz            #+#    #+#             */
/*   Updated: 2026/05/14 18:04:14 by muhaoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	cheat_putstr(char *s)
{
	int	i;

	if (!s)
	{
		return (write(1, "(null)", 6));
	}
	i = 0;
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
	return (i);
}

static int	cheat_hex_magic(unsigned long n, char *b)
{
	int				len;
	unsigned int	blen;

	len = 0;
	blen = 0;
	while (b[blen])
		blen++;
	if (n >= blen)
		len += cheat_hex_magic(n / blen, b);
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
	len += cheat_hex_magic(num, "0123456789");
	return (len);
}

static int	cheat_summon(char t, va_list *ap)
{
	unsigned long	p;

	if (t == 'c')
	{
		t = (char)va_arg(*ap, int);
		return (write(1, &t, 1));
	}
	if (t == 's')
		return (cheat_putstr(va_arg(*ap, char *)));
	if (t == 'p')
	{
		p = (unsigned long)va_arg(*ap, void *);
		if (!p)
			return (write(1, "(nil)", 5));
		return (write(1, "0x", 2) + cheat_hex_magic(p, "0123456789abcdef"));
	}
	if (t == 'd' || t == 'i')
		return (cheat_number_spit(va_arg(*ap, int)));
	if (t == 'u')
		return (cheat_hex_magic(va_arg(*ap, unsigned int), "0123456789"));
	if (t == 'x')
		return (cheat_hex_magic(va_arg(*ap, unsigned int), "0123456789abcdef"));
	if (t == 'X')
		return (cheat_hex_magic(va_arg(*ap, unsigned int), "0123456789ABCDEF"));
	return (0);
}

int	ft_printf(const char *s, ...)
{
	va_list	ap;
	int		i;
	int		len;

	if (!s)
		return (va_end(ap), -1);
	va_start(ap, s);
	i = -1;
	len = 0;
	while (s[++i])
	{
		if (s[i] != '%')
			len += write(1, &s[i], 1);
		else if (!s[++i])
			return (va_end(ap), -1);
		else if (s[i] == '%')
			len += write(1, "%", 1);
		else
			len += cheat_summon(s[i], &ap);
	}
	return (va_end(ap), len);
}
