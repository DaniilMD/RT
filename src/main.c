#include "rtv1.h"

void			loading_message(t_sdl *sdl)
{
	SDL_Surface	*load;
	SDL_Rect	load_rect;

	load_rect.x = 0;
	load_rect.y = 0;
	load = SDL_LoadBMP("loading.bmp");
	SDL_BlitSurface(load, NULL, sdl->screen, &load_rect);
	SDL_FreeSurface(load);
}

void			run_gui(t_sdl *sdl)
{
	SDL_Event	event;

	SDL_CreateWindowAndRenderer(C_W, C_H, 0, &(sdl->window), &(sdl->renderer));
	sdl->screen = SDL_CreateRGBSurface(0, C_W, C_H, 32, 0x00FF0000,\
							0x0000FF00, 0x000000FF, 0xFF000000);
	sdl->texture = SDL_CreateTexture(sdl->renderer, SDL_PIXELFORMAT_ARGB8888,\
								SDL_TEXTUREACCESS_STREAMING, C_W, C_H);
	loading_message(sdl);
	progress_bar(sdl, 0.1);
	while (SDL_PollEvent(&event))
	{
	}
	sdl->cl_inst = initcl(sdl);
}

void			quit_sdl(t_sdl *sdl)
{
	SDL_FreeSurface(sdl->screen);
	SDL_DestroyWindow(sdl->window);
	SDL_Quit();
}

int				main(int argc, char **argv)
{
	t_sdl		sdl;
	t_scene		scene;

	if (argc < 2)
		return (0);
	sdl.scenes = argv;
	sdl.scene_num = argc - 1;
	scene.current_scene = 1;
	if (!construct_scene(argv[1], &scene, &sdl))
	{
		run_gui(&sdl);
		ft_draw(sdl, scene);
		controls(sdl, scene);
		releasecl(&(sdl.cl_inst));
		quit_sdl(&sdl);
	}
	return (0);
}
