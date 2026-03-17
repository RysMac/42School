#include <fcntl.h>

#include "get_next_line.h"

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 9
#endif

char	*get_next_line(int fd)
{
	char		*line; // whole line must be returned so no need to be static
	static char	*temp; // part of the text which left from buffer
	char		buffer[BUFFER_SIZE + 1];
	ssize_t		bytes_read;
	size_t		position;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	if (temp)
	{
		line = ft_strdup(temp, 0, ft_strlen(temp));
		free(temp);
		temp = NULL;
	}
	while (1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(line);
			return (NULL);
		}
		if (bytes_read == 0)
			break;
		buffer[bytes_read] = '\0';
		line = ft_join_and_free(line, buffer);

		if (ft_strlen_end_line(buffer, &position) == 1 || bytes_read == 0)
		{
			temp = ft_strdup(buffer, position, BUFFER_SIZE);
			return (line);
		}
	}
}



int	main()
{
	int				fd;

	fd = open("next_line_txt.txt" ,O_RDONLY);
	//fd = open("textfile.txt" ,O_RDONLY);
	if (fd < 0) return 1;

	for (int i = 0; i < 20; i++){
		//printf("full line out = %s", get_next_line(fd));
		printf("%s", get_next_line(fd));
	}


	// for (int i = 0; i < bytes_read; i++) {
	// 	printf("Char: %c  ASCII: %d\n", buffer[i], buffer[i]);
	// }

	//printf("buffer size = %d \n", BUFFER_SIZE);
	//printf("koniec \n");
	return 0;
}
