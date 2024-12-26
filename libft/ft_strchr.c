#include "libft.h"

char    *ft_strchr(const char *str, int c)
{
    while (*str)
    {
        if (*str == (unsigned char)c)
            return ((char *)str);
        str++;
    }
    if ((unsigned char)c == '\0')
        return ((char *)str);
    return (0);
}