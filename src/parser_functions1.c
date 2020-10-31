#include "rtv1.h"

cl_float3		return_zero_vector(void)
{
	cl_float3	zero;

	zero.s[0] = 0;
	zero.s[1] = 0;
	zero.s[2] = 0;
	return (zero);
}

cl_float2		return_zero_2dvector(void)
{
	cl_float2	zero;

	zero.s[0] = 0;
	zero.s[1] = 0;
	return (zero);
}

cl_float4		return_zero_4dvector(void)
{
	cl_float4	zero;

	zero.s[0] = 0;
	zero.s[1] = 0;
	zero.s[2] = 0;
	zero.s[3] = 0;
	return (zero);
}

cl_int3			return_zero_color(void)
{
	cl_int3		zero;

	zero.s[0] = 0;
	zero.s[1] = 0;
	zero.s[2] = 0;
	return (zero);
}

cl_float3		parse_vector(char *str)
{
	cl_float3	v;

	if (!ft_strchr(str, '('))
		return (return_zero_vector());
	str = ft_strchr(str, '(') + 1;
	v.s[0] = ft_atof(str);
	if (!ft_strchr(str, ','))
		return (return_zero_vector());
	str = ft_strchr(str, ',') + 1;
	v.s[1] = ft_atof(str);
	if (!ft_strchr(str, ','))
		return (return_zero_vector());
	str = ft_strchr(str, ',') + 1;
	v.s[2] = ft_atof(str);
	if (!ft_strchr(str, ')'))
		return (return_zero_vector());
	return (v);
}
