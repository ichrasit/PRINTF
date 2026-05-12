/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhaoz <muhaoz@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 15:34:32 by muhaoz            #+#    #+#             */
/*   Updated: 2026/05/12 15:36:21 by muhaoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	cheat_putchar(char c)
{
	return (write(1, &c, 1));
}

static int	cheat_putstr(char *s)
{
	int	i;

	if (!s)
		return (write(1, "(null)", 6));
	i = 0;
	while (s[i])
		i += cheat_putchar(s[i]);
	return (i);
}

static int	cheat_number_spit(long n)
{
	int		len;
	char	g;

	len = 0;
	if (n < 0)
	{
		len += cheat_putchar('-');
		n = -n;
	}
	if (n >= 10)
		len += cheat_number_spit(n / 10);
	g = (char)((n % 10) + '0');
	len += cheat_putchar(g);
	return (len);
}

static int	cheat_unholy_unsigned(unsigned int x)
{
	int		len;
	char	h;

	len = 0;
	if (x >= 10)
		len += cheat_unholy_unsigned(x / 10);
	h = (char)((x % 10) + '0');
	len += cheat_putchar(h);
	return (len);
}

static int	cheat_hex_magic(unsigned long o, char *b)
{
	int	len;

	len = 0;
	if (o >= 16)
		len += cheat_hex_magic(o / 16, b);
	len += cheat_putchar(b[o % 16]);
	return (len);
}

static int	cheat_summon(char token, va_list ap)
{
	if (token == CH_C)
		return (cheat_putchar(va_arg(ap, int)));
	if (token == CH_S)
		return (cheat_putstr(va_arg(ap, char *)));
	if (token == CH_D || token == CH_I)
		return (cheat_number_spit(va_arg(ap, int)));
	if (token == CH_U)
		return (cheat_unholy_unsigned(va_arg(ap, unsigned int)));
	if (token == CH_X)
		return (cheat_hex_magic(va_arg(ap, unsigned int),
				"0123456789abcdef"));
	if (token == CH_XX)
		return (cheat_hex_magic(va_arg(ap, unsigned int),
				"0123456789ABCDEF"));
	if (token == CH_P)
	{
		write(1, "0x", 2);
		return (2 + cheat_hex_magic((unsigned long)va_arg(ap, void *),
				"0123456789abcdef"));
	}
	if (token == CH_PERCENT)
		return (cheat_putchar('%'));
	return (0);
}

int	ft_printf(const char *s, ...)
{
	va_list	ap;
	int		i;
	int		len;

	va_start(ap, s);
	i = 0;
	len = 0;
	if(!s)
		return(va_end(ap), -1);
	while (s[i])
	{
		if (s[i] == '%' && s[i + 1])
		{
			len += cheat_summon(s[i + 1], ap);
			i += 2;
		}
		else
		{
			len += cheat_putchar(s[i]);
			i++;
		}
	}
	va_end(ap);
	return (len);
}
