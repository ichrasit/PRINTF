#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

typedef int	(*t_fmt_func)(va_list);

int	ft_printf(const char *format, ...);
int handle_c(va_list args);
int handle_s(va_list args);
int handle_pct(va_list args);
int handle_d(va_list args);
int handle_u(va_list args);
int ft_print_num(unsigned long n, char *base);
int ft_print_num(unsigned long n, char *base);
#endif