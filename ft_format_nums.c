/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_nums.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhaoz <muhaoz@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 02:11:48 by muhaoz            #+#    #+#             */
/*   Updated: 2026/08/19 02:12:19 by muhaoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	handle_d(va_list args)
{
	long	n;

	n = va_arg(args, int);
	if (n < 0)
		return (write(1, "-", 1) + ft_print_num(-n, "0123456789"));
	return (ft_print_num(n, "0123456789"));
}

int	handle_u(va_list args)
{
	return (ft_print_num(va_arg(args, unsigned int), "0123456789"));
}
