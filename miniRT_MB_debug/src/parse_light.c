#include "parse.h"

void	parse_light(char **s, t_scene *scene)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	
	if (len != 3 && len != 4)
		exit_error("Invalid light format (L pos brightness [color])");

	parse_vec3(s[1], scene->light.pos);
	scene->light.brightness = parse_double(s[2]);
	if (scene->light.brightness < 0.0 || scene->light.brightness > 1.0)
		exit_error("Light brightness must be in [0,1]");

	// Jeśli jest kolor – wczytaj, jeśli nie – domyślnie biały
	if (len == 4)
		parse_color(s[3], scene->light.color);
	else
	{
		scene->light.color[0] = 1.0;
		scene->light.color[1] = 1.0;
		scene->light.color[2] = 1.0;
	}
}
