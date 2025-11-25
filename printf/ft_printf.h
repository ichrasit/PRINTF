#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdint.h>

# define CH_C 'c'
# define CH_S 's'
# define CH_D 'd'
# define CH_I 'i'
# define CH_U 'u'
# define CH_X 'x'
# define CH_XX 'X'
# define CH_P 'p'
# define CH_PERCENT '%'

int		ft_printf(const char *s, ...);

#endif
