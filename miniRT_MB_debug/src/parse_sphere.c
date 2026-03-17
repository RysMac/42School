#include "parse.h"

void	parse_sphere(char **s, t_scene *scene)
{
	t_inputdata	in;
	t_obj		obj;
	double		diameter;
	size_t		len;

	len = 0;
	while (s[len])
		len++;
	if (len != 4)
		exit_error("Invalid sphere format (sp pos diameter color)");
	ft_bzero(&in, sizeof(in));
	parse_vec3(s[1], in.pos);
	diameter = parse_double(s[2]);
	if (diameter <= 0.0)
		exit_error("Sphere diameter must be positive");
	in.radius = diameter / 2.0;
	parse_color(s[3], in.albedo);
	obj_sphere(&obj, &in);
	add_object(scene, &obj);
}
