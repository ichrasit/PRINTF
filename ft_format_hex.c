#include "ft_printf.h"

int handle_x_low(va_list args)
{
    return (ft_print_num(va_arg(args, unsigned int), "0123456789abcdef"));
}

int handle_x_up(va_list args)
{
    return (ft_print_num(va_arg(args, unsigned int), "0123456789ABCDEF"));
}

int handle_p(va_list args)
{
    unsigned long   p;

    p = (unsigned long)va_arg(args, void *);
    if(!p)
        return(write(1, "(nil)", 5));
    return(write(1, "0x", 2) + ft_print_num(p, "0123456789abcdef"));
}
