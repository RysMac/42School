#include "libft.h"

char    *ft_strrchr(const char *str, int c)
{
    const char *ptr;

    ptr = NULL;
    while (*str)
    {
        if (*str == (unsigned char)c)
            ptr = str;
        str++;
    }
    if ((unsigned char)c == '\0')
        return ((char *)str);
    return ((char *)ptr);
}
