/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_grid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mr <mr@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 13:20:16 by mrys              #+#    #+#             */
/*   Updated: 2025/05/20 20:06:58 by mr               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	grid_size(int *w, int *h, char *name)
{
	int		fd;
	char	*line;
	char	**str;

	fd = read_file(name);
	*h = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line || ft_strlen(line) == 0)
			break ;
		if (line && *h == 0)
		{
			*w = 0;
			str = ft_split(line, ' ');
			while (str[*w])
				(*w)++;
			free_loop(str);
		}
		(*h)++;
		free(line);
	}
	free(line);
	close(fd);
}

t_point	**grid_alloc(int w, int h)
{
	int		i;
	int		j;
	t_point	**grid;

	grid = malloc(sizeof(t_point *) * h);
	if (!grid)
		return (NULL);
	i = 0;
	while (i < h)
	{
		grid[i] = malloc(sizeof(t_point) * w);
		if (!grid[i])
		{
			j = 0;
			while (j < i)
				free(grid[j]);
			free(grid);
			return (NULL);
		}
		i++;
	}
	return (grid);
}

char	**splitting(int fd)
{
	char	*line;
	char	**split;

	line = get_next_line(fd);
	split = ft_split(line, ' ');
	free(line);
	return (split);
}

static t_point	parse_point(int row, int col, char *txt)
{
	t_point	point;
	char	**split;

	point.x = col;
	point.y = row;
	point.screen_x = col;
	point.screen_y = row;
	if (!txt)
		point.z = 0;
	else
	{
		split = ft_split(txt, ',');
		point.z = ft_atoi(split[0]);
	}
	if (!split[1])
		point.color = 0xFFFFFF;
	else
	{
		point.color = hex_to_int(split[1]);
		// printf("split1 color = %d \n", point.color);
	}
	free_loop(split);
	return (point);
}

t_point	**grid2d(int w, int h, char *name)
{
	int		i;
	int		j;
	int		fd;
	t_point	**grid;
	char	**split;

	fd = read_file(name);
	grid = grid_alloc(w, h);
	i = 0;
	while (i < h)
	{
		split = splitting(fd);
		j = 0;
		while (j < w)
		{
			grid[i][j] = parse_point(i, j, split[j]);
			j++;
		}
		i++;
		free_loop(split);
	}
	close(fd);
	return (grid);
}
