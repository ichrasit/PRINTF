#include <unistd.h>
#include "ft_printf.h"
#include <stdarg.h>
#include <stdio.h>

void topla(int count, ...){
    va_list arg;
    va_start(arg, count);
    int  sum = 0;
    int i = 0;

    while(i < count){
        sum += va_arg(arg, int);
        i++;
    }
    printf("%d", sum);
    va_end(arg);
}

int main(){
    topla(5, 10, 15, 20, 30);
};