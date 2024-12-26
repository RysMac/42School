#include "libft.h"

size_t  ft_strlen(const char *str)
{
    size_t  c;

    if (!str)
        return 0;
    
    c = 0;
    while (str[c])
    {
        c++;
    }
    return  (c);
}