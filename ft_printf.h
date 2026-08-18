/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhaoz <muhaoz@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 02:11:53 by muhaoz            #+#    #+#             */
/*   Updated: 2026/08/19 02:40:50 by muhaoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

typedef int	(*t_fmt_func)(va_list);

int			ft_printf(const char *format, ...) __attribute__((format(printf, 1,
						2)));
int			handle_c(va_list args);
int			handle_s(va_list args);
int			handle_pct(va_list args);
int			handle_d(va_list args);
int			handle_u(va_list args);
int			handle_x_low(va_list args);
int			handle_x_up(va_list args);
int			handle_p(va_list args);
int			ft_print_num(unsigned long n, char *base);

#endif