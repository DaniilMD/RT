#include "rtv1.h"

void			get_object_parameters(t_cl_object *object, char *str)
{
	get_object_parameters_inner(object, str);
	if (ft_strstr(str, "alpha:"))
		object->alpha = ft_atof(ft_strstr(str, "alpha:") + 6) / 180. * M_PI;
	if (ft_strstr(str, "specular:"))
		object->specular = ft_atoi(ft_strstr(str, "specular:") + 9);
	if (ft_strstr(str, "reflective:"))
		object->reflective = ft_atof(ft_strstr(str, "reflective:") + 11) > 1
				? 1 : ft_atof(ft_strstr(str, "reflective:") + 11);
	if (ft_strstr(str, "transparent:"))
		object->refractive = ft_atof(ft_strstr(str, "transparent:") + 12) > 1
				? 1 : ft_atof(ft_strstr(str, "transparent:") + 12);
	if (ft_strstr(str, "tex_num:"))
		object->texture = ft_atoi(ft_strstr(str, "tex_num:") + 8);
	if (ft_strstr(str, "tex_type:"))
		object->textype = parse_type(ft_strstr(str, "tex_type:") + 9);
	if (ft_strstr(str, "shift:"))
		object->shift = parse_2dvector(ft_strstr(str, "shift:") + 6);
	if (ft_strstr(str, "scale:"))
		object->scale = parse_2dvector(ft_strstr(str, "scale:") + 6);
	get_slices(object, str);
	if (ft_strstr(str, "negative:"))
		object->negative = ft_atoi(ft_strstr(str, "negative:") + 9);
	if (ft_strstr(str, "index_of_refr:"))
		object->index_of_refr = ft_atof(ft_strstr(str, "index_of_refr:") + 14);
}

char			parse_object_type(char *str)
{
	if (ft_strstr(str, "plane"))
		return ('p');
	if (ft_strstr(str, "sphere"))
		return ('s');
	if (ft_strstr(str, "cyl"))
		return ('c');
	if (ft_strstr(str, "cone"))
		return ('t');
	return ('n');
}

cl_float3		norm_v(cl_float3 vector)
{
	cl_float	len;
	cl_float3	out;

	len = vector.s0 * vector.s0;
	len += vector.s1 * vector.s1;
	len += vector.s2 * vector.s2;
	out.s0 = vector.s0 / sqrt(len);
	out.s1 = vector.s1 / sqrt(len);
	out.s2 = vector.s2 / sqrt(len);
	return (out);
}

t_matrix		return_eig_rot_m(cl_float3 cam_ang)
{
	int			i;
	t_matrix	zero;

	ft_memset(zero.m, 0, sizeof(zero.m));
	i = -1;
	while (++i < 3)
		zero.m[i][i] = 1;
	cam_ang.s[0] = cam_ang.s[0] * (3.14 / 180);
	cam_ang.s[1] = cam_ang.s[1] * (3.14 / 180);
	zero.m[0][0] = cos(cam_ang.s[1]);
	zero.m[0][1] = 0;
	zero.m[0][2] = sin(cam_ang.s[1]);
	zero.m[1][0] = sin(cam_ang.s[1]) * sin(cam_ang.s[0]);
	zero.m[1][1] = cos(cam_ang.s[0]);
	zero.m[1][2] = -sin(cam_ang.s[0]) * cos(cam_ang.s[1]);
	zero.m[2][0] = -sin(cam_ang.s[1]) * cos(cam_ang.s[0]);
	zero.m[2][1] = sin(cam_ang.s[0]);
	zero.m[2][2] = cos(cam_ang.s[0]) * cos(cam_ang.s[1]);
	return (zero);
}

cl_float3		ft_vrot(cl_float3 a, t_matrix rot)
{
	cl_float3	res;

	res.s[0] = rot.m[0][0] * a.s[0] + rot.m[0][1] *\
		a.s[1] + rot.m[0][2] * a.s[2];
	res.s[1] = rot.m[1][0] * a.s[0] + rot.m[1][1] *\
		a.s[1] + rot.m[1][2] * a.s[2];
	res.s[2] = rot.m[2][0] * a.s[0] + rot.m[2][1] *\
		a.s[1] + rot.m[2][2] * a.s[2];
	return (res);
}
