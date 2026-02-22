/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrys <mrys@student.42warsaw.pl>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 11:16:37 by mrys              #+#    #+#             */
/*   Updated: 2026/02/22 11:16:37 by mrys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include <stddef.h>

typedef struct s_obj	t_obj;
/*  c - camera center
	f - forward direction
	r - right
	u - up
*/
typedef struct s_camera
{
	int		w;
	int		h;
	double	fovx;
	double	fovy;
	double	c[3];
	double	f[3];
	double	r[3];
	double	u[3];
}	t_camera;

typedef struct s_light
{
	double	pos[3];
	double	brightness;
	double	color[3];
}	t_light;

// ambient_color -> input 0-255 -> rescale for 0-1
typedef struct s_ambient
{
	double	ambient_ratio;
	double	ambient_color[3];
}	t_ambient;

/*
	objects - pointer to whole list of objects
	count - number of all objs
*/
typedef struct s_scene
{
	t_camera	camera;
	t_light		light;
	t_ambient	ambient;
	t_obj		*objects;
	size_t		count;
}	t_scene;

#endif