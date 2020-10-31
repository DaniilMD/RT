#include "rtv1.h"

void			pencil(cl_int4 *z, int i)
{
	cl_int4		*back;
	size_t		size;

	size = sizeof(cl_int4);
	back = (cl_int4*)malloc(size * C_H * C_W);
	grayscale(z, 10);
	back = ft_memcpy(back, z, sizeof(cl_int4) * C_H * C_W);
	invert(back);
	box_blur(back, i);
	dodge(z, back);
	free(back);
}

void			three_d(t_sdl sdl, t_scene scene, cl_int4 *z)
{
	cl_int4		*z_add;
	int			i;

	scene.viewpoint.s0 += 0.5;
	z_add = rt_cl(&(sdl.cl_inst), scene);
	i = -1;
	while (++i < C_W * C_H)
	{
		z[i].s[1] = z_add[i].s[1];
		z[i].s[2] = z_add[i].s[2];
	}
	free(z_add);
}

void			antialiasing(cl_int4 *z, int n)
{
	int			i;
	int			j;
	int			x;
	int			y;

	x = 0;
	while (x < C_W * n)
	{
		y = 0;
		while (y < C_H * n)
		{
			i = -1;
			z[x / n * C_H + y / n] = (cl_int4){{0, 0, 0, 0}};
			while (++i < n)
			{
				j = -1;
				while (++j < n)
					vector_sum(z + x / n * C_H + y / n, z[((x + i) * n) * C_H
					+ y + j]);
			}
			vector_div_n(z + x / n * C_H + y / n, pow(n, 2));
			y += n;
		}
		x += n;
	}
}

void			norm(cl_int4 *z)
{
	int			x;
	int			y;

	x = -1;
	while (++x < C_W)
	{
		y = -1;
		while (++y < C_H)
		{
			if (z[x * C_H + y].s[0] > 255)
				z[x * C_H + y].s[0] = 255;
			if (z[x * C_H + y].s[1] > 255)
				z[x * C_H + y].s[1] = 255;
			if (z[x * C_H + y].s[2] > 255)
				z[x * C_H + y].s[2] = 255;
		}
	}
}

void			effect(cl_int4 *z, t_sdl sdl, t_scene scene)
{
	norm(z);
	if (scene.effect == 's')
		sepia(z);
	else if (scene.effect == 'g')
		grayscale(z, scene.effect_int);
	else if (scene.effect == 'b')
		box_blur(z, scene.effect_int);
	else if (scene.effect == 'p')
		pixelize(z, scene.effect_int);
	else if (scene.effect == 'i')
		invert(z);
	else if (scene.effect == 'l')
		pencil(z, scene.effect_int);
	else if (scene.effect == 't')
		three_d(sdl, scene, z);
	else if (scene.effect == 'a')
		antialiasing(z, scene.effect_int);
}
