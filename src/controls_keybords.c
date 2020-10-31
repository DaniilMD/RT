#include "rtv1.h"

void		keyboard_effects_inner(t_sdl sdl, t_scene *scene,\
const Uint8 *keystate)
{
	scene->effect_int = 3;
	if (keystate[SDL_SCANCODE_O])
		scene->effect = scene->effect != 's' ? 's' : 0;
	if (keystate[SDL_SCANCODE_G])
		scene->effect = scene->effect != 'g' ? 'g' : 0;
	if (keystate[SDL_SCANCODE_P])
		scene->effect = scene->effect != 'p' ? 'p' : 0;
	if (keystate[SDL_SCANCODE_I])
		scene->effect = scene->effect != 'i' ? 'i' : 0;
	if (keystate[SDL_SCANCODE_L])
		scene->effect = scene->effect != 'l' ? 'l' : 0;
	if (keystate[SDL_SCANCODE_B])
		scene->effect = scene->effect != 'b' ? 'b' : 0;
	if (keystate[SDL_SCANCODE_Y])
		scene->effect = scene->effect != 'a' ? 'a' : 0;
	if (keystate[SDL_SCANCODE_T])
		scene->effect = scene->effect != 't' ? 't' : 0;
	ft_draw(sdl, *scene);
}

void		keyboard_sdl_scancode_pageup(t_sdl sdl, t_scene *scene)
{
	if (scene->current_scene == 1)
		scene->current_scene = sdl.scene_num;
	else
		scene->current_scene--;
	if (!construct_scene(sdl.scenes[scene->current_scene], scene, &sdl))
		ft_draw(sdl, *scene);
}

void		keyboard_sdl_scancode_pagedown(t_sdl sdl, t_scene *scene)
{
	if (scene->current_scene == sdl.scene_num)
		scene->current_scene = 1;
	else
		scene->current_scene++;
	if (!construct_scene(sdl.scenes[scene->current_scene], scene, &sdl))
		ft_draw(sdl, *scene);
}

void		keyboard_sdl_scancode_plus(t_scene *scene)
{
	if (scene->effect == 'a')
		scene->effect_int += scene->effect_int < 4 ? 1 : 0;
	else
		scene->effect_int += scene->effect_int < 10 ? 1 : 0;
}

void		keyboard_sdl_scancode_h(t_sdl *sdl, t_scene scene)
{
	sdl->help = sdl->help != 1 ? 1 : 0;
	ft_draw(*sdl, scene);
}
