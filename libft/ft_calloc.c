#include "libft.h"
/**
 * Function Name: ft_calloc
 * Description:
 *     allocates memory and zero it out
 *
 * Parameters:
 *     - nmemb (size_t): n elements of some type.
 *     - size (size_t): the size of each element.
 *
 * Return Value:
 *     Returns a pointer to memory
 */
void    *ft_calloc(size_t nmemb, size_t size)
{
    size_t  total_size;
    size_t  i;
    void    *m_ptr;
    unsigned char   *byte_ptr;

    total_size = nmemb * size;
    m_ptr = malloc(total_size);
    if (!m_ptr)
        return (NULL);

    byte_ptr = (unsigned char *)m_ptr;
    i = 0;
    while (i < total_size)
    {
        byte_ptr[i] = 0;
        i++;
    }
    return (m_ptr);
}