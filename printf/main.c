#include "ft_printf.h"
#include <stdio.h>


int main()
{
    ft_printf("Uzunluk : %d\n", ft_printf("%s %d %c %i %p %x %X %u", "rasit", 42, 'a', 42, 42, 42, 42, 42));
    printf("Uzunluk : %d", printf("%s %d %c %i %p %x %X %u", "rasit", 42, 'a', 42, 42, 42, 42, 42));
}