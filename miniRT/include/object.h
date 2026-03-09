/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrys <mrys@student.42warsaw.pl>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 11:31:20 by mrys              #+#    #+#             */
/*   Updated: 2026/02/22 11:31:20 by mrys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_obj	t_obj;

typedef struct s_vec3
{
	double	v[3];
}	t_vec3;

typedef struct s_ray
{
	double	o[3];
	double	d[3];
}	t_ray;

/*	hit position in world
	normal in world,
	unit oriented
	pointer to object for albedo info
*/
typedef struct s_hit
{
	double		t;
	double		p[3];
	double		n[3];
	const t_obj	*obj;
}	t_hit;

// typedef int	(*t_intersect_fn)(const t_obj *self,
		//  const t_ray *ray, t_hit *hit);

// object type
typedef enum s_obj_type
{
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYLINDER,
	OBJ_INVALID
}	t_obj_type;

/*	object position/orientation in global frame
	for sphere the origin, for plane normal etc
	pos - position in the world space
	dir - orientation axis / normal (unit ector)
*/
typedef struct s_obj_pos
{
	double	pos[3];
	double	dir[3];
}	t_obj_pos;

// plane needs nothing
// sphere -> needs radius info
typedef struct s_sphere
{
	double	radius;
}	t_sphere;

// cylinder -> needs axis
typedef struct s_cylinder
{
	double	radius;
	double	height;
}	t_cylinder;

// generic shape data: tagged by t_obj_type
typedef union u_shape_data
{
	t_sphere	sphere;
	t_cylinder	cylinder;
}	t_shape_data;

// whole object info
typedef struct s_obj
{
	t_obj_type		type;
	t_obj_pos		pos;
	t_shape_data	shape;
	int				(*intersect)(const struct s_obj *self,
			const t_ray *ray, t_hit *hit);
	double			albedo[3];
}	t_obj;
