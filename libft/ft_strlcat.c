#include "libft.h"

size_t  ft_strlcat(char *dest, const char *src, size_t dstsize)
{
    size_t  i;
    size_t  dest_len;
    size_t  src_len;

    dest_len = ft_strlen(dest);
    src_len = ft_strlen(src);
    
    if (dstsize <= dest_len)
        return (dstsize + src_len); 

    i = 0;
    while (i < src_len && dest_len + i <= dstsize - 1)
    {
        dest[dest_len + i] = src[i];
        i++;
    }
    dest[dest_len + i] = '\0';
    return (dest_len + src_len);
}