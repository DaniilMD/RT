#include "cl/ray_trace.h"

t_ray		obj_refl(t_ray od, t_ray pr, int closest, t_scene scene)
{
	
	//od.d = apply_bump(od, scene.objects[closest], scene.objects[closest].dist);
	
	od.d = od.d * (-1);
	pr.d = pr.d * (2.0f * dot(pr.d, od.d)) - od.d;
	pr.d = normalize(pr.d);
	return (pr);
}

t_ray		obj_refr(t_ray od, t_ray pr, int closest, t_scene scene)
{
	t_ray		refr;
	float		tetta_1;
	float		n_dot_i;

	float3		normal;
	float3		i;

	float		eta;
	float		etai;
	float		etat;

	// set normal
	// normal = normalize(pr.d);
	// // crossing point
	// refr.o = pr.o; //od.o + (od.d * scene.objects[closest].dist);
	// // incident ray
	// i = normalize(od.d);
	// n_dot_i = dot(normal, i);
	// etai = 1;
	// etat = scene.objects[closest].index_of_refr;
	// if (n_dot_i < 0)
	// {
	// 	//n_dot_i = -n_dot_i;
	// 	eta = -(etai - etat);
	// 	i /= etat;
	// }
	// else
	// {
	// 	eta = -(etat - etai);
	// 	i *= etat;
	// }
	// float cs = n_dot_i * length(i);//(dot(normal, i) / (length(normal) * length(i)));
	// refr.d = i + (sqrt(cs * cs + (etat + etai) * (eta)) - cs) * normal;
	// refr.d = normalize(refr.d);
	// return (refr);

	normal = pr.d;
	// crossing point
	refr.o = pr.o; //od.o + (od.d * scene.objects[closest].dist);
	// incident ray
	i = od.d;
	n_dot_i = dot(normal, i);
	etai = 1;
	etat = scene.objects[closest].index_of_refr;
	if (n_dot_i < 0)
	{
		n_dot_i = -n_dot_i;
		eta = etai / etat;
	}
	else
	{
		pr.d = -pr.d;
		eta = etat / etai;
	}
	// 1st angle (incident angle)
	tetta_1 = acos(n_dot_i / (length(normal) * length(i)));
	// refr ray dir
	refr.d = eta * (i + cos(tetta_1) * normal) -\
		normal * sqrt(1 - eta * eta * sin(tetta_1) * sin(tetta_1));
	return (refr);
}