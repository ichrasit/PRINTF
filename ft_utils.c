/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhaoz <muhaoz@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 02:11:56 by muhaoz            #+#    #+#             */
/*   Updated: 2026/08/19 02:12:31 by muhaoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_num(unsigned long n, char *base)
{
	char			buf[21];
	int				i;
	int				len;
	unsigned long	blen;

	i = 0;
	len = 0;
	blen = 0;
	while (base[blen])
		blen++;
	if (n == 0)
		return (write(1, &base[0], 1));
	while (n > 0)
	{
		buf[i++] = base[n % blen];
		n /= blen;
	}
	while (i > 0)
	{
		i--;
		len += write(1, &buf[i], 1);
	}
	return (len);
}
