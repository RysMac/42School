#include "libft.h"

void    *ft_memmove(void *dest, const void *src, size_t n)
{
    size_t  i;
    unsigned char   *d;
    const unsigned char   *s;

    if (!dest || !src)
        return  (NULL);

    d = (unsigned char *)dest;
    s = (const unsigned char *)src;
    if (d > s && d < s + n)
    {
        while(n)
        {
            n--;
            d[n] = s[n];
        }
    }
    else
    {
        i = 0;
        while (i < n)
        {
            d[i] = s[i];
            i++;
        }
    }
    return  (dest);
}