#include "ft_printf.h"
#include <stdio.h>

int main(){
	printf("Null pointer : %p\n", NULL);
	ft_printf("Null pointer : %p", NULL);
}