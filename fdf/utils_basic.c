/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_basic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mr <mr@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 13:15:34 by mrys              #+#    #+#             */
/*   Updated: 2025/05/20 20:05:18 by mr               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	read_file(char *name)
{
	int	fd;
	char *path;
	char *full_name;
	char *full_path;

	path = "maps/test_maps/";
	full_name = ft_strjoin(name, ".fdf");
	printf("full_name: %s \n", full_name);
	full_path = ft_strjoin(path, full_name);

	fd = open(full_path, O_RDONLY);
	if (fd < 0)
	{
		perror("file name ... argv[1] \n");
		exit(1);
	}
	free(full_name);
	free(full_path);
	return (fd);
}

void	free_loop(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_grid(t_point **grid, int h)
{
	int	i;

	i = 0;
	while (i < h)
	{
		free(grid[i]);
		i++;
	}
	free(grid);
}

int	hex_to_int(const char *hex)
{
	int		result = 0;
	char	c;

	if (hex[0] == '0' && (hex[1] == 'x' || hex[1] == 'X'))
		hex += 2;

	while ((c = *hex++))
	{
		result *= 16;
		if (c >= '0' && c <= '9')
			result += c - '0';
		else if (c >= 'a' && c <= 'f')
			result += c - 'a' + 10;
		else if (c >= 'A' && c <= 'F')
			result += c - 'A' + 10;
		else
			break ;
	}
	return result;
}
