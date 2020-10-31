#include "cl/ray_trace.h"

t_ray		new_pr(t_ray od, t_object obj, float dist)
{
	t_ray		pr;

	pr.o = od.o + (od.d * dist);
	if (obj.type == 's')
	{
		pr.d = pr.o - (obj.center);
	}
	else if (obj.type == 'p')
	{
		pr.d = obj.norm;
	}
	else if (obj.type == 'c')
	{
		pr.d = pr.o - obj.center;
		pr.d = cross(pr.d, obj.norm);
		pr.d = cross(obj.norm, pr.d);
	}
	else if (obj.type == 't')
	{
		pr.d = pr.o - obj.center;
		pr.d = cross((obj.norm * dot(obj.norm, pr.d)), pr.d);
		pr.d = cross(pr.d, (pr.o - obj.center));
	}
	if (obj.textype == 'b')
		pr.d = apply_bump(pr, obj, dist);

	pr.d = normalize(pr.d);
	return (pr);
}

float3		apply_bump(t_ray od, t_object obj, float dist)
{
	float3		texture;
	float3		norm;

		norm = od.d * (1.0f / length(od.d));
		texture = gtexture(obj, norm, od.o);
		od.d = normalize(od.d) + normalize(cross(od.d, (float3)(1.0f, 0.0f, 0.0f))) * (texture.x / 255) + normalize(cross(od.d, (float3)(0.0f, 1.0f, 0.0f))) * (texture.y / 255);
	return(od.d);
}

float3		obj_col(t_ray pr, t_object obj)
{
	float3		back;

	back = convert_float3(obj.color);
	if (obj.textype == 'c')
		back = gtexture(obj, pr.d, pr.o);
	return (back);
}