#include "rtv1.h"

void			vector_div_n(cl_int4 *z, int n)
{
	z->s0 /= n;
	z->s1 /= n;
	z->s2 /= n;
}

void			vector_sum(cl_int4 *z, cl_int4 add)
{
	z->s0 += add.s0;
	z->s1 += add.s1;
	z->s2 += add.s2;
	z->s3++;
}

cl_int4			ret_vector_div_n(cl_int4 a, int n)
{
	cl_int4	b;

	b.s0 = a.s0 / n;
	b.s1 = a.s1 / n;
	b.s2 = a.s2 / n;
	return (b);
}

void			box_blur(cl_int4 *z, int n)
{
	cl_int4		sum;
	int			d[2];
	int			i[2];

	d[0] = -1;
	while (++d[0] < C_W)
	{
		d[1] = -1;
		while (++d[1] < C_H)
		{
			sum = (cl_int4){{0, 0, 0, 1}};
			i[0] = -n - 1;
			while (++i[0] < n + 1)
			{
				i[1] = -n - 1;
				while (++i[1] < n + 1)
					if (d[0] + i[0] < C_W && d[1] + i[1] < C_H \
							&& d[0] + i[0] > 0 && d[1] + i[1] > 0)
						vector_sum(&sum, z[(d[0] + i[0])\
						* C_H + (d[1] + i[1])]);
			}
			z[d[0] * C_H + d[1]] = ret_vector_div_n(sum, sum.s[3]);
		}
	}
}

void			make_pixelize(int *c, int n, cl_int4 *z, cl_int4 sum)
{
	int			i[2];

	i[0] = -1;
	while (++i[0] < n)
	{
		i[1] = -1;
		while (++i[1] < n)
			if (c[0] * n + i[0] < C_W && c[1] * n + i[1] < C_H && \
				c[0] * n + i[0] > 0 && c[1] * n + i[1] > 0)
				z[(c[0] * n + i[0]) * C_H + (c[1] * n +
								i[1])] = ret_vector_div_n(sum, sum.s3);
	}
}
