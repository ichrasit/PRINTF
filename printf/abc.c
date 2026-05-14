#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

// void    function(int count, ...)
// {
//     va_list ag;
//     va_start(ag, count);
//     int sum = 0;
//     int i = 0;
//     while(i < count)
//     {
//         sum += va_arg(ag, int);
//         i++;
//     }
//     printf("%d", sum);
//     va_end(ag);
// }

// int main()
// {  
   
//     function(5, 10, 20, 30, 40, 50);
    
// }



int strlenght(char *s)
{
    int i = 0;
    while(s[i])
        i++;
    return i;
}


char    *strjoiner(char *first, ...)
{
    va_list ap;
    char *str;
    char *tmp;
    int len = 0;
    int i =0;
    va_start(ap, first);
    tmp = first;
    while(tmp)
    {
        len += strlenght(tmp);
        tmp = va_arg(ap, char* );
    }
    va_end(ap);
    str = malloc(len + 1);
    if(!str)
        return NULL;

    va_start(ap ,first);
    tmp = first;
    while(tmp)
    {
        int j = 0;
        while(tmp[j])
            str[i++] = tmp[j++];
        tmp = va_arg(ap, char *);
    }
    str[i] = '\0';
    va_end(ap);
    return str;


}

int main()
{
    char *s = strjoiner("selam ", "kızlar ", "sikim ", "sızlar", NULL);
    printf("%s\n", s);
    free(s);
}
