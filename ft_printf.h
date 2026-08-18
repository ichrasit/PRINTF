#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

typedef int	(*t_fmt_func)(va_list);

int	ft_printf(const char *format, ...);

#endif