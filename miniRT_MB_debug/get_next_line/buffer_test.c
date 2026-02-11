#include <fcntl.h>

#include "get_next_line.h"

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 20
#endif


char	*get_next_line(int fd)
{
	static char	*tmp_line;
	static char	*full_line;
	size_t		length;
	size_t		is_end;
	char		buffer[BUFFER_SIZE + 1];


	ssize_t bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read > 0)
		buffer[bytes_read] = '\0';  // Ensure proper string termination
	else
		return (NULL);

	length = 0;
	if (full_line)
		if (ft_strlen_end_line(full_line, &length) == 1)
			free(full_line);

	ft_strlen_end_line(buffer, &length);
	if ((!full_line || is_end == 1) && !tmp_line)
		full_line = ft_strdup(buffer, 0, length);
	else if (is_end && tmp_line)
	{
		full_line = tmp_line;
		full_line = ft_strjoin(full_line, buffer);
		free(tmp_line);
	}
	else
		full_line = ft_strjoin(full_line, buffer);


	if (length < BUFFER_SIZE)
		tmp_line = ft_strdup(buffer, length, BUFFER_SIZE);

	// printf("buffer : %s \n", buffer);
	// printf("malloc line :%s \n", tmp_line);
	// printf("malloc full line :%s \n", full_line);

	if (ft_strlen_end_line(full_line, &length) == 1)
		return (full_line);
	else
		return ('\0');
}


int	main()
{
	int				fd;

	fd = open("next_line_txt.txt" ,O_RDONLY);
	//fd = open("textfile.txt" ,O_RDONLY);
	if (fd < 0) return 1;

	for (int i = 0; i < 50; i++){
		printf("full line out = %s \n", get_next_line(fd));
	}


	// for (int i = 0; i < bytes_read; i++) {
	// 	printf("Char: %c  ASCII: %d\n", buffer[i], buffer[i]);
	// }

	printf("buffer size = %ld \n", BUFFER_SIZE);
	printf("koniec \n");
	return 0;
}
