#include "rtv1.h"

int		construct_scene(char *fname, t_scene *scene, t_sdl *sdl)
{
	char	*str;

	str = ft_strjoin("RT, current scene: ", fname);
	SDL_SetWindowTitle(sdl->window, str);
	free(str);
	if (ft_parse_scene(fname, scene))
		return (1);
	scene->startviewpoint = scene->viewpoint;
	scene->cl_lim.max = 1.001f;
	scene->cl_lim.min = 0.001f;
	scene->tr_lim.max = 400000.0f;
	scene->tr_lim.min = 0.001f;
	scene->effect = 0;
	scene->effect_int = 1;
	scene->width = C_W;
	scene->height = C_H;
	return (0);
}
