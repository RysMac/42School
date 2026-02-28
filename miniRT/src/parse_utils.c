/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrys <mrys@student.42warsaw.pl>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 12:37:39 by mrys              #+#    #+#             */
/*   Updated: 2026/02/28 18:02:35 by mrys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include <math.h>

void	parse_vec3(char *s, double v[3])
{
	char	**t;
	size_t	i;

	t = ft_split(s, ',');
	i = 0;
	while (t && t[i])
		i++;
	if (i != 3)
		exit_error("Invalid vector format (expected x,y,z)");
	v[0] = parse_double(t[0]);
	v[1] = parse_double(t[1]);
	v[2] = parse_double(t[2]);
	ft_free_tab(t);
}

void	parse_color(char *s, double c[3])
{
	parse_vec3(s, c);
	if (c[0] < 0.0 || c[0] > 255.0 || c[1] < 0.0 || c[1] > 255.0
		|| c[2] < 0.0 || c[2] > 255.0)
		exit_error("Color values must be in [0-255]");
	c[0] /= 255.0;
	c[1] /= 255.0;
	c[2] /= 255.0;
}

int	is_normalized(double v[3])
{
	double	norm;

	norm = vnorm3(v);
	if (norm < 1e-6)
		exit_error("Zero vector not allowed");
	return (fabs(norm - 1.0) < 1e-6);
}

void	add_object(t_scene *scene, t_obj *obj)
{
	t_obj	*new;
	size_t	i;

	new = malloc(sizeof(t_obj) * (scene->count + 1));
	if (!new)
		exit_error("malloc failed");
	i = 0;
	while (i < scene->count)
	{
		new[i] = scene->objects[i];
		i++;
	}
	new[i] = *obj;
	free(scene->objects);
	scene->objects = new;
	scene->count++;
	printf("new object added\n");
}

void	ft_free_tab(char **tab)
{
	size_t	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
