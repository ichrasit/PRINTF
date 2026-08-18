/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_nums.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhaoz <muhaoz@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 02:11:48 by muhaoz            #+#    #+#             */
/*   Updated: 2026/08/19 02:40:45 by muhaoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	handle_d(va_list args)
{
	long	n;
	int		tmp1;
	int		tmp2;

	n = va_arg(args, int);
	if (n < 0)
	{
		tmp1 = write(1, "-", 1);
		if (tmp1 == -1)
			return (-1);
		tmp2 = ft_print_num(-n, "0123456789");
		if (tmp2 == -1)
			return (-1);
		return (tmp1 + tmp2);
	}
	return (ft_print_num(n, "0123456789"));
}

int	handle_u(va_list args)
{
	return (ft_print_num(va_arg(args, unsigned int), "0123456789"));
}
