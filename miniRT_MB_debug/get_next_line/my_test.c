/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_test.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mr <mr@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 23:17:59 by mr                #+#    #+#             */
/*   Updated: 2025/01/13 14:39:04 by mr               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <fcntl.h>

int	main()
{
	int		i;
	int		fd;

	fd = open("textfile.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return 1;
	}

	i = 0;
	while (i < 8)
	{
		printf("%s\n", get_next_line(fd));
		i++;
	}


	close(fd);

	return 0;
}
