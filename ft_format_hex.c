/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhaoz <muhaoz@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 02:11:42 by muhaoz            #+#    #+#             */
/*   Updated: 2026/08/21 06:34:43 by muhaoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	handle_x_low(va_list args)
{
	return (ft_print_num(va_arg(args, unsigned int), "0123456789abcdef"));
}

int	handle_x_up(va_list args)
{
	return (ft_print_num(va_arg(args, unsigned int), "0123456789ABCDEF"));
}

int	handle_p(va_list args)
{
	int				tmp1;
	int				tmp2;
	unsigned long	p;

	p = (unsigned long)va_arg(args, void *);
	if (!p)
		return (write(1, "(nil)", 5));
	tmp1 = write(1, "0x", 2);
	if (tmp1 == -1)
		return (-1);
	tmp2 = ft_print_num(p, "0123456789abcdef");
	if (tmp2 == -1)
		return (-1);
	return (tmp1 + tmp2);
}
