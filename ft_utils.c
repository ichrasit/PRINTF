/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhaoz <muhaoz@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 02:11:56 by muhaoz            #+#    #+#             */
/*   Updated: 2026/08/21 06:32:59 by muhaoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	flush_buffer(char *buf, int i)
{
	int	len;
	int	tmp;

	len = 0;
	while (i > 0)
	{
		i--;
		tmp = write(1, &buf[i], 1);
		if (tmp == -1)
			return (-1);
		len += tmp;
	}
	return (len);
}

int	ft_print_num(unsigned long n, char *base)
{
	char			buf[21];
	unsigned long	blen;
	int				i;

	blen = 0;
	while (base[blen])
		blen++;
	if (n == 0)
		return (write(1, &base[0], 1));
	i = 0;
	while (n > 0)
	{
		buf[i++] = base[n % blen];
		n /= blen;
	}
	return (flush_buffer(buf, i));
}
