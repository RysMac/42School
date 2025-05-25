#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define  BUFFER_SIZE 42
# endif

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

size_t	ft_strlen(char const *str);
size_t	ft_strlen_end_line(const char *str, size_t *length);
char	*ft_strdup_gnl(const char *str, size_t start, size_t finish);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_join_and_free(char *text, char *buffer);
char	*get_next_line(int fd);

#endif
