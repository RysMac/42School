#include "libft.h"

void    *ft_memset(void *s, int c, size_t n)
{
    /*
    function fills the first n bytes of the memory area pointed to by s with the constant byte c
    */
    size_t  i;
    unsigned char   *ptr;

    if (!s)
        return (NULL);

    ptr = (unsigned char *)s;
    i = 0;
    while (i < n)
    {
        ptr[i] = (unsigned char)c;
        i++;
    }
    return (s);
}
