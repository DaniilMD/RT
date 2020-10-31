#include "rtv1.h"

cl_float2		parse_2dvector(char *str)
{
	cl_float2	v;

	if (!ft_strchr(str, '('))
		return (return_zero_2dvector());
	str = ft_strchr(str, '(') + 1;
	v.s[0] = ft_atof(str);
	if (!ft_strchr(str, ','))
		return (return_zero_2dvector());
	str = ft_strchr(str, ',') + 1;
	v.s[1] = ft_atof(str);
	if (!ft_strchr(str, ')'))
		return (return_zero_2dvector());
	return (v);
}

cl_float4		parse_4dvector(char *str)
{
	cl_float4	v;

	if (!ft_strchr(str, '('))
		return (return_zero_4dvector());
	str = ft_strchr(str, '(') + 1;
	v.s[0] = ft_atof(str);
	if (!ft_strchr(str, ','))
		return (return_zero_4dvector());
	str = ft_strchr(str, ',') + 1;
	v.s[1] = ft_atof(str);
	if (!ft_strchr(str, ','))
		return (return_zero_4dvector());
	str = ft_strchr(str, ',') + 1;
	v.s[2] = ft_atof(str);
	if (!ft_strchr(str, ','))
		return (return_zero_4dvector());
	str = ft_strchr(str, ',') + 1;
	v.s[3] = ft_atof(str);
	if (!ft_strchr(str, ')'))
		return (return_zero_4dvector());
	return (v);
}

cl_int3			parse_color(char *str)
{
	cl_int3		color;

	color = return_zero_color();
	if (!str)
		return (color);
	if (!ft_strchr(str, '('))
		return (color);
	str = ft_strchr(str, '(') + 1;
	color.s[0] = ft_atoi(str);
	if (!ft_strchr(str, ','))
		return (color);
	str = ft_strchr(str, ',') + 1;
	color.s[1] = ft_atoi(str);
	if (!ft_strchr(str, ','))
		return (color);
	color.s[2] = ft_atoi(ft_strchr(str, ',') + 1);
	return (color);
}

char			parse_type(char *str)
{
	while (*str == ' ' || *str == '\n')
		str++;
	return (*str);
}

void			get_slices(t_cl_object *object, char *str0)
{
	int			i;
	char		*str;

	str = str0;
	i = -1;
	while (++i < 4 && ft_strstr(str, "slice:"))
	{
		str = ft_strstr(str, "slice:") + 6;
		object->slice[i] = parse_4dvector(str);
	}
	str = str0;
	i = -1;
	while (++i < 4 && ft_strstr(str, "slice_side:"))
	{
		str = ft_strstr(str, "slice_side:") + 11;
		object->slice_side[i] = ft_atoi(str);
	}
}
