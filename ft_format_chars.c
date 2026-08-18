#include "ft_printf.h"

int handle_c(va_list args)
{
    char    c;

    c = (char)va_arg(args, int);
    return (write(1, &c, 1));
}

int handle_s(va_list args)
{
    char *s;
    int len;

    s = va_arg(args, char *);
    if(!s)
        return (write(1, "(null)", 6));
    len = 0;
    while(s[len])
        len++;
    return(write(1, s, len));
}

int handle_pct(va_list args)
{
    (void)args;
    return(write(1, "%", 1));
}
