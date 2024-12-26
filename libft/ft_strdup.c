#include "libft.h"

char *ft_strdup(const char *str)
{
    size_t  len;
    size_t  i;
    char    *ptr;

    len = ft_strlen(str);
    ptr = (char *)malloc(sizeof(char) * (len + 1));
    if (!ptr)
        return (NULL);
    
    i = 0;
    while (i < len)
    {
        ptr[i] = str[i];
        i++;
    }
    
    ptr[i] = '\0';
    return (ptr);
}