#include "libft.h"

int ft_strncmp(const char *str1, const char *str2, size_t n)
{
    size_t  i;
    unsigned char   *s1;
    unsigned char   *s2;

    if (n == 0)
        return (0);

    s1 = (unsigned char *)str1;
    s2 = (unsigned char *)str2;
    
    i = 0;
    while (s1[i] && s2[i] && i < n)
    {
        if (s1[i] != s2[i])
            return (s1[i] - s2[i]);
        i++;
    }
    return (s1[i] - s2[i]);
}