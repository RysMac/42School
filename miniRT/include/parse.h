/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrys <mrys@student.42warsaw.pl>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 11:19:16 by mrys              #+#    #+#             */
/*   Updated: 2026/02/28 18:02:23 by mrys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "scene.h"
# include "framebuffer.h"
# include "../libft/libft.h" 

typedef struct s_flags
{
    int has_a;
    int has_c;
    int has_l;
}   t_flags;

void	parse_file(const char *path, t_scene *scene);
void	parse_line(char *line, t_scene *scene, t_flags *flags);

void	parse_ambient(char **split, t_scene *scene);
void	parse_camera(char **split, t_scene *scene);
void	parse_light(char **split, t_scene *scene);
void	parse_sphere(char **split, t_scene *scene);
void	parse_plane(char **split, t_scene *scene);
void	parse_cylinder(char **split, t_scene *scene);

void	add_object(t_scene *scene, t_obj *obj);
double	parse_double(char *s);
void	parse_vec3(char *s, double v[3]);
void	parse_color(char *s, double c[3]);
double	parse_double_internal(const char *str);
int		is_normalized(double v[3]);
int		is_number(char *s);
void	exit_error(const char *msg);
void	ft_free_tab(char **tab);

#endif
