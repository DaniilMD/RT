
#include "cl/ray_trace.h"


int			get_closest(t_ray od, t_object *objects, float *dist, t_lim lim)
{
	int obj;
	t_roots	roots;
	int i = 0;
	t_roots	tmp;

	*dist = INF;
	obj = -1;
	roots.root1 = INF;
	roots.root2 = INF;
	while (i < 20)
	{
		roots = ft_intersect_ray_obj(od.o, od.d, objects[i]);
		if (objects[i].type == 'p')
		{
			if (roots.root2 == INF && roots.root1 != INF)
				objects[i].norm *= -1;
		}
		if (objects[i].slice_side[0] > 0)
			slicer(objects[i], &roots,	od.o, od.d);
		if (roots.root1 < *dist && roots.root1 >= lim.min && roots.root1 <= lim.max)
		{
			*dist = roots.root1;
			obj = i;
			tmp.root2 = roots.root2;
			tmp.root1 = roots.root1;
		}
		if (roots.root2 < *dist && roots.root2 >= lim.min && roots.root2 <= lim.max)
		{
			*dist = roots.root2;
			obj = i;
			tmp.root2 = roots.root2;
			tmp.root1 = roots.root1;
		}

		i++;
	}
	if (obj != -1 && objects[obj].negative == 1)
	{
		if (tmp.root1  > 0 &&  tmp.root2 > 0)
		{
			if (tmp.root1 < tmp.root2)
				*dist = tmp.root2;
			else
				*dist = tmp.root1;
		}
		
	}
	// if (obj != -1 &&  objects[obj].trans > 0)
	// {
	// 	if (tmp.root1  > 0 &&  tmp.root2 > 0)
	// 	{
	// 		if (tmp.root1 < tmp.root2)
	// 			*dist = tmp.root2;
	// 		else
	// 			*dist = tmp.root1;
	// 	}
		
	// }
	return (obj);
}

int4		ft_trace_ray(t_ray od, t_lim lim, t_scene scene, int depth)
{
	int			closest;
	float		dist;
	float3		back;
	int 		obj;

	t_ray  r1;
	float3	f1;

	back = (float3)(0.0f, 0.0f, 0.0f);
	closest = get_closest(od, scene.objects, &(dist), lim);
	if (closest == -1)
		return ((int4)(convert_int3(back), closest));

	if (scene.objects[closest].negative == 1)
	{
		od.o = od.o + od.d * dist * 1.0001f;
		closest = get_closest(od, scene.objects, &(dist), lim);
		if (closest == -1)
			return ((int4)(convert_int3(back), closest));
	}


	scene.objects[closest].dist = dist;

	r1 = new_pr(od, scene.objects[closest], dist);
	back = obj_col(r1, scene.objects[closest]);
	back *= compute_lighting(r1, od.d, scene, scene.objects[closest].specular, closest);

	if (scene.objects[closest].reflective > 0) {
		depth = 1;
		int 		me, i = 0;
		float3		tmp_back;

		back = back * (1 - scene.objects[closest].reflective);
		while (i < depth)
		{
			od = obj_refl(od, r1, closest, scene);
			me = closest;
			closest = get_closest(od, scene.objects, &(dist), lim);
			scene.objects[closest].dist = dist;
			
			if (closest >= 0 &&  scene.objects[me].reflective > 0 ) 
			{
				r1 = new_pr(od, scene.objects[closest], dist); 		
				tmp_back = obj_col(r1, scene.objects[closest]);
				tmp_back *= compute_lighting(r1, od.d, scene, scene.objects[closest].specular, closest);
				tmp_back *= scene.objects[me].reflective;
				if (i < depth - 1)
					tmp_back *= (1 - scene.objects[closest].reflective);
				back += tmp_back;

			}
			else break ;
		 	++i;
		}
	}
	else if (scene.objects[closest].refractive > 0)
	{
		depth = 4;
		int 		me, i = 0;
		float3		tmp_back;
		back = back * (1 - scene.objects[closest].refractive);

		while (i < depth)
		{
			od = obj_refr(od, r1, closest, scene);
			me = closest;
			closest = get_closest(od, scene.objects, &(dist), lim);
			scene.objects[closest].dist = dist;
			
			if (closest >= 0 &&  scene.objects[me].refractive > 0) 
			{
				r1 = new_pr(od, scene.objects[closest], dist); 		
				tmp_back = obj_col(r1, scene.objects[closest]);
				tmp_back *= compute_lighting(r1, od.d, scene, scene.objects[closest].specular, closest);
				tmp_back *= scene.objects[me].refractive;
				if (i < depth - 1)
					tmp_back *= (1 - scene.objects[closest].refractive);
				if (i % 2)
					back += tmp_back * scene.objects[me].refractive;

			}
			else break ;
		 	++i;
		}
	}
	return ((int4)(convert_int3(back), obj));
}

float3		ft_vrot(float3 a, t_matrix rot)
{
	float3	res;

	res.x = rot.m[0][0] * a.x + rot.m[0][1] * a.y + rot.m[0][2] * a.z;
	res.y = rot.m[1][0] * a.x + rot.m[1][1] * a.y + rot.m[1][2] * a.z;
	res.z = rot.m[2][0] * a.x + rot.m[2][1] * a.y + rot.m[2][2] * a.z;
	return (res);
}

float3		ft_canvas_to_viewport(int x, int y, int width, int height)
{
	float3	viewport;
	int		min;

	if (width < height)
		min = width;
	else
		min = height;
	viewport.x = (1.0f / min) * x - 0.5f / min * width;
	viewport.y = - (1.0f / min) * y + 0.5f / min * height;
	viewport.z = 1.0f;
	return (viewport);
}

__kernel void render(__global int4 *output, t_scene scene)
{
	int work_item_id = get_global_id(0);
	int y_coord = work_item_id % scene.height ;
	int x_coord = work_item_id / scene.height ;
	int4 finalcolor;

	t_lim		lim;
	t_ray		od;

	lim.min = 0.001f;
	lim.max = INF;
	
	od.o = scene.viewpoint;
	
	od.d = ft_vrot(ft_canvas_to_viewport(x_coord, y_coord, scene.width, scene.height), scene.rot_matrix);
	od.d = od.d / length(od.d);
	finalcolor = ft_trace_ray(od, lim, scene, 4);
	finalcolor.x = finalcolor.x > 255 ? 255 : finalcolor.x;
	finalcolor.y = finalcolor.y > 255 ? 255 : finalcolor.y;
	finalcolor.z = finalcolor.z > 255 ? 255 : finalcolor.z;
	output[work_item_id] = finalcolor;
}
