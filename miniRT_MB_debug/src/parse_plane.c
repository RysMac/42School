#include "parse.h"

void	parse_plane(char **s, t_scene *scene)
{
	t_inputdata	in;
	t_obj		obj;
	size_t		len;

	len = 0;
	while (s[len])
		len++;
	if (len != 4)
		exit_error("Invalid plane format (pl pos normal color)");
	ft_bzero(&in, sizeof(in));
	parse_vec3(s[1], in.pos);
	parse_vec3(s[2], in.ndir);
	if (!is_normalized(in.ndir))
		exit_error("Plane normal not normalized");
	parse_color(s[3], in.albedo);
	obj_plane(&obj, &in);
	add_object(scene, &obj);
}
