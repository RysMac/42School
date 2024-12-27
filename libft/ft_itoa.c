#include "libft.h"

char    *ft_itoa(int n)
{
    size_t  l;
    int  i;
    int sign;
    unsigned int    n_copy;
    unsigned int    temp;
    char    *ptr;

    sign = 0;
    if (n < 0)
    {
        n_copy = (unsigned int)(-n);
        sign = 1;
    }
    else
        n_copy = (unsigned int)(n);

    if (n == 0)
        l = 1;
    else
        l = 0;
    temp = n_copy;
    while (temp > 0)
    {
        temp /= 10;
        l++;
    }
    l += sign;

    ptr = (char *)malloc(l + 1);
    if (!ptr)
        return (NULL);
    ptr[l] = '\0';

    i = l - 1;
    while (i >= 0)
    {
        if (sign == 1 && i == 0)
        {
            ptr[0] = '-';
        }
        else
        {
            ptr[i] = (n_copy % 10) + '0';
            n_copy /= 10;
        }
        i--;
    }
    return (ptr);
}
