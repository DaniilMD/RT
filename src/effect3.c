#include "rtv1.h"

void			pixelize(cl_int4 *z, int n)
{
	cl_int4		sum;
	int			c[2];
	int			i[2];

	c[0] = -1;
	while (++c[0] * n < C_W)
	{
		c[1] = -1;
		while (++c[1] * n < C_H)
		{
			sum = (cl_int4){{0, 0, 0, 1}};
			i[0] = -1;
			while (++i[0] < n + 1)
			{
				i[1] = -1;
				while (++i[1] < n + 1)
					if (c[0] * n + i[0] < C_W && c[1] * n + i[1] < C_H && \
									c[0] * n + i[0] > 0 && c[1] * n + i[1] > 0)
						vector_sum(&sum, z[(c[0] * n + i[0]) * C_H\
							+ (c[1] * n + i[1])]);
			}
			make_pixelize(c, n, z, sum);
		}
	}
}

void			sepia(cl_int4 *z)
{
	int			x;
	int			y;
	int			tmp_r;
	int			tmp_g;

	x = -1;
	while (++x < C_W)
	{
		y = -1;
		while (++y < C_H)
		{
			tmp_r = z[x * C_H + y].s[0];
			tmp_g = z[x * C_H + y].s[1];
			z[x * C_H + y].s[0] = (tmp_r * .393)\
			+ (tmp_g * .769) + (z[x * C_H + y].s[2] * .189);
			z[x * C_H + y].s[1] = (tmp_r * .349)\
			+ (tmp_g * .686) + (z[x * C_H + y].s[2] * .168);
			z[x * C_H + y].s[2] = (tmp_r * .272)\
			+ (tmp_g * .534) + (z[x * C_H + y].s[2] * .131);
		}
	}
}

void			grayscale(cl_int4 *z, int i)
{
	int			x;
	int			y;
	int			tmp_r;
	int			tmp_g;
	int			gray;

	x = -1;
	while (++x < C_W)
	{
		y = -1;
		while (++y < C_H)
		{
			tmp_r = z[x * C_H + y].s[0];
			tmp_g = z[x * C_H + y].s[1];
			gray = (tmp_r * .3) + (tmp_g * .59) + (z[x * C_H + y].s[2] * .11);
			z[x * C_H + y].s[0] = (tmp_r * (10 - i) + gray * i) / 10;
			z[x * C_H + y].s[1] = (tmp_g * (10 - i) + gray * i) / 10;
			z[x * C_H + y].s[2] = (z[x * C_H + y].s[2] * (10 - i) + gray * i)
				/ 10;
		}
	}
}

void			invert(cl_int4 *z)
{
	int			x;
	int			y;

	x = -1;
	while (++x < C_W)
	{
		y = -1;
		while (++y < C_H)
		{
			z[x * C_H + y].s[0] = abs(255 - z[x * C_H + y].s[0]);
			z[x * C_H + y].s[1] = abs(255 - z[x * C_H + y].s[1]);
			z[x * C_H + y].s[2] = abs(255 - z[x * C_H + y].s[2]);
		}
	}
}

void			dodge(cl_int4 *front, cl_int4 *back)
{
	int			x;
	int			y;

	x = -1;
	while (++x < C_W)
	{
		y = -1;
		while (++y < C_H)
		{
			front[x * C_H + y].s[0] = back[x * C_H + y].s[0] == 255 ? 255 : \
				front[x * C_H + y].s[0] * 255 / (255 - back[x * C_H + y].s[0]);
			front[x * C_H + y].s[1] = back[x * C_H + y].s[1] == 255 ? 255 : \
				front[x * C_H + y].s[1] * 255 / (255 - back[x * C_H + y].s[1]);
			front[x * C_H + y].s[2] = back[x * C_H + y].s[2] == 255 ? 255 : \
				front[x * C_H + y].s[2] * 255 / (255 - back[x * C_H + y].s[2]);
		}
	}
}
