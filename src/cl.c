#include "rtv1.h"

void			progress_bar(t_sdl *sdl, float percent)
{
	SDL_Rect rect;

	rect.x = 300;
	rect.y = 400;
	rect.w = 500;
	rect.h = 50;
	SDL_UpdateTexture(sdl->texture, NULL, sdl->screen->pixels,
		sdl->screen->pitch);
	SDL_RenderClear(sdl->renderer);
	SDL_RenderCopy(sdl->renderer, sdl->texture, NULL, NULL);
	if (percent < 0.f)
		percent = 0.f;
	if (percent > 1.f)
		percent = 1.f;
	SDL_SetRenderDrawColor(sdl->renderer, 0, 0, 0, 255);
	SDL_RenderDrawRect(sdl->renderer, &rect);
	rect.w = percent * 500;
	SDL_RenderFillRect(sdl->renderer, &rect);
	SDL_RenderPresent(sdl->renderer);
}

t_cl			initcl(t_sdl *sdl)
{
	t_cl		cl;
	cl_uint		rnd;
	cl_uint		ret_num_platforms;
	int			fd;

	fd = open("cl/alltogether.cl", O_RDONLY);
	cl.source_str = (char*)malloc(500000000);
	cl.source_size = read(fd, cl.source_str, 500000000);
	close(fd);
	clGetPlatformIDs(1, &cl.platform_id, &ret_num_platforms);
	clGetDeviceIDs(cl.platform_id, CL_DEVICE_TYPE_DEFAULT, 1, &cl.dev_id, &rnd);
	cl.context = clCreateContext(NULL, 1, &cl.dev_id, NULL, NULL, NULL);
	cl.command_queue = clCreateCommandQueue(cl.context, cl.dev_id, 0, NULL);
	progress_bar(sdl, 0.2);
	cl.program = clCreateProgramWithSource(cl.context, 1,
		(const char **)&cl.source_str, (const size_t *)&cl.source_size, NULL);
	progress_bar(sdl, 0.3);
	cl.z_clmem = clCreateBuffer(cl.context, CL_MEM_WRITE_ONLY,
		16 * C_H * C_W * sizeof(cl_int4), NULL, NULL);
	progress_bar(sdl, 0.4);
	clBuildProgram(cl.program, 1, &cl.dev_id, NULL, NULL, NULL);
	progress_bar(sdl, 0.5);
	cl.kernel = clCreateKernel(cl.program, "render", NULL);
	progress_bar(sdl, 0.6);
	return (cl);
}

cl_int3			*rt_cl(t_cl *cl, t_scene scene)
{
	cl_int4		*z;
	size_t		global_item_size;
	size_t		local_item_size;

	global_item_size = C_H * C_W;
	if (scene.effect == 'a')
	{
		scene.width *= scene.effect_int;
		scene.height *= scene.effect_int;
		global_item_size *= pow(scene.effect_int, 2);
	}
	local_item_size = 256;
	z = (cl_int4 *)malloc(sizeof(cl_int4) * global_item_size);
	clSetKernelArg(cl->kernel, 0, sizeof(cl_mem), (void *)&cl->z_clmem);
	clSetKernelArg(cl->kernel, 1, sizeof(t_scene), &(scene));
	clEnqueueNDRangeKernel(cl->command_queue, cl->kernel, 1, NULL,
			&global_item_size, &local_item_size, 0, NULL, NULL);
	clEnqueueReadBuffer(cl->command_queue, cl->z_clmem, CL_TRUE, 0,
			global_item_size * sizeof(cl_int4), z, 0, NULL, NULL);
	clFlush(cl->command_queue);
	clFinish(cl->command_queue);
	return (z);
}
