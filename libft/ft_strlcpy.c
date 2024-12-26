#include "libft.h"

size_t  ft_strlcpy(char *dest, const char *src, size_t dstsize)
{
    size_t  i;
    size_t  src_len;

    if (!dest || !src)
        return (0);

    src_len = 0;
    while (src[src_len] != '\0')
        src_len++;
    if (dstsize == 0)
        return (src_len); //ft_strlen(char src)

    i = 0;
    while (i < dstsize - 1 && src[i] != '\0')
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return  (src_len);
}