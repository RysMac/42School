#include "parse.h"

void	parse_camera(char **s, t_scene *scene)
{
	double	f[3];
	double	c[3];
	double	fov;
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	if (len != 4)
		exit_error("Invalid camera format (C pos dir fov)");
	parse_vec3(s[1], c);
	parse_vec3(s[2], f);
	if (!is_normalized(f))
		exit_error("Camera direction not normalized");
	fov = parse_double(s[3]);
	if (fov < 0.0 || fov > 180.0)
		exit_error("FOV must be in [0,180]");
	camera_set(&scene->camera, 800, 600, fov, f, c);
}
