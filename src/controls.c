#include "rtv1.h"

static void		mouse_controls(t_sdl sdl, t_scene *scene, SDL_Event event)
{
	cl_float3	shift;

	shift = (cl_float3){{0, 0, 1}};
	shift = ft_vrot(shift, scene->rot_matrix);
	if (event.wheel.y > 0)
	{
		scene->viewpoint.s[0] += shift.s[0];
		scene->viewpoint.s[1] += shift.s[1];
		scene->viewpoint.s[2] += shift.s[2];
	}
	else if (event.wheel.y < 0)
	{
		scene->viewpoint.s[0] -= shift.s[0];
		scene->viewpoint.s[1] -= shift.s[1];
		scene->viewpoint.s[2] -= shift.s[2];
	}
	ft_draw(sdl, *scene);
}

void			camera_movement(t_sdl sdl, t_scene *scene, SDL_Event event)
{
	cl_float3	shift;
	int			sym;

	shift = (cl_float3){{0, 0, 0}};
	sym = event.key.keysym.sym;
	if (sym == SDLK_d || sym == SDLK_a || sym == SDLK_w || sym == SDLK_s)
	{
		if (event.key.keysym.sym == SDLK_d)
			shift = ft_vrot((cl_float3){{1, 0, 0}}, scene->rot_matrix);
		else if (event.key.keysym.sym == SDLK_a)
			shift = ft_vrot((cl_float3){{-1, 0, 0}}, scene->rot_matrix);
		else if (event.key.keysym.sym == SDLK_w)
			shift = ft_vrot((cl_float3){{0, 1, 0}}, scene->rot_matrix);
		else if (event.key.keysym.sym == SDLK_s)
			shift = ft_vrot((cl_float3){{0, -1, 0}}, scene->rot_matrix);
		scene->viewpoint.s[0] += shift.s[0];
		scene->viewpoint.s[1] += shift.s[1];
		scene->viewpoint.s[2] += shift.s[2];
		ft_draw(sdl, *scene);
	}
}

void			camera_rotation(t_sdl sdl, t_scene *scene, SDL_Event event)
{
	int			sym;

	sym = event.key.keysym.sym;
	if (sym == SDLK_DOWN || sym == SDLK_UP || sym == SDLK_RIGHT || sym ==
	SDLK_LEFT)
	{
		if (sym == SDLK_DOWN)
			scene->cam_angles.s[0] += 5;
		else if (sym == SDLK_UP)
			scene->cam_angles.s[0] -= 5;
		else if (sym == SDLK_RIGHT)
			scene->cam_angles.s[1] += 5;
		else if (sym == SDLK_LEFT)
			scene->cam_angles.s[1] -= 5;
		scene->rot_matrix = return_eig_rot_m(scene->cam_angles);
		ft_draw(sdl, *scene);
	}
}

void			keyboard_effects(t_sdl sdl, t_scene *scene, const Uint8
*keystate)
{
	if (keystate[SDL_SCANCODE_RETURN])
		SDL_SaveBMP(sdl.screen, "screenshot.bmp");
	if (keystate[SDL_SCANCODE_SPACE] && \
	(keystate[SDL_SCANCODE_O] || keystate[SDL_SCANCODE_G] ||
	keystate[SDL_SCANCODE_P] || keystate[SDL_SCANCODE_I] ||
	keystate[SDL_SCANCODE_L] || keystate[SDL_SCANCODE_B] ||
	keystate[SDL_SCANCODE_Y] || keystate[SDL_SCANCODE_T]))
		keyboard_effects_inner(sdl, scene, keystate);
	else if (keystate[SDL_SCANCODE_KP_PLUS] || keystate[SDL_SCANCODE_KP_MINUS])
	{
		if (keystate[SDL_SCANCODE_KP_PLUS])
			keyboard_sdl_scancode_plus(scene);
		else if (keystate[SDL_SCANCODE_KP_MINUS])
			scene->effect_int -= scene->effect_int > 1 ? 1 : 0;
		ft_draw(sdl, *scene);
	}
	else if (keystate[SDL_SCANCODE_PAGEDOWN] || keystate[SDL_SCANCODE_PAGEUP])
	{
		if (keystate[SDL_SCANCODE_PAGEDOWN])
			keyboard_sdl_scancode_pagedown(sdl, scene);
		else if (keystate[SDL_SCANCODE_PAGEUP])
			keyboard_sdl_scancode_pageup(sdl, scene);
	}
}

void			controls(t_sdl sdl, t_scene scene)
{
	SDL_Event	event;
	const Uint8	*keystate;

	keystate = SDL_GetKeyboardState(NULL);
	while (1)
	{
		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				break ;
			else if (event.type == SDL_MOUSEWHEEL)
				mouse_controls(sdl, &scene, event);
			else if (event.type == SDL_KEYDOWN)
			{
				controls_inner_cam(&sdl, &scene, event, keystate);
				if (keystate[SDL_SCANCODE_H])
					keyboard_sdl_scancode_h(&sdl, scene);
				if (event.key.keysym.sym == SDLK_ESCAPE || \
						event.key.keysym.sym == SDLK_q)
					break ;
			}
		}
		if (scene.animate == 1)
			controls_inner_sdl_scene(sdl, &scene);
	}
}
