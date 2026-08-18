#include "ft_printf.h"

int handle_d(va_list args)
{
    long    n;
    
    n = va_arg(args, int);
    if(n < 0)
        return (write(1, "-", 1) + ft_print_num(-n, "0123456789"));
    return (ft_print_num(n, "0123456789"));
}

int handle_u(va_list args)
{
    return (ft_print_num(va_arg(args, unsigned int), "0123456789"));
}
