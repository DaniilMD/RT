#include "rtv1.h"

void				controls_inner_sdl_scene(t_sdl sdl, t_scene *scene)
{
	static float	ani;

	ani = ani + 0.05;
	if (ani > 3.14 * 2)
		ani = 0;
	scene->objects[0].shift.s[0] = scene->objects[0].shift.s[0] + 0.01;
	scene->objects[0].center.s[0] = scene->objects[0].center.s[0]\
			- cos(ani - 0.1) * 2 + cos(ani) * 2;
	scene->objects[0].center.s[1] = scene->objects[0].center.s[1]\
			- sin(ani - 0.1) * 2 + sin(ani) * 2;
	scene->objects[1].center.s[0] = scene->objects[1].center.s[0]\
			- cos(ani - 0.1) * 2 + cos(ani) * 2;
	scene->objects[1].center.s[2] = scene->objects[1].center.s[2]\
			- sin(ani - 0.1) * 2 + sin(ani) * 2;
	ft_draw(sdl, *scene);
}

void				controls_inner_cam(t_sdl *sdl, t_scene *scene,\
SDL_Event event, const Uint8 *keystate)
{
	camera_movement(*sdl, scene, event);
	camera_rotation(*sdl, scene, event);
	keyboard_effects(*sdl, scene, keystate);
}
