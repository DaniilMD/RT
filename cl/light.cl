#include "cl/ray_trace.h"


/*float		compute_lighting(t_ray pn, float3 md, t_scene scene, int specular, int closest)
{
	float		intensities;
	t_source	s;
	t_ray		pl;
	t_ray		tmp;
	float		dist;
	float		tmpdist;
	int			i = -1;
	float		plane_vp;
	float		d;
	int 		obj;
	float		modifier = 1.;

	intensities = 0.0f;
	pl.o = pn.o;
	if (scene.objects[closest].type == 'p')
	{
		d = -1. * dot(scene.objects[closest].norm, scene.objects[closest].center);
		plane_vp = dot(scene.objects[closest].norm, scene.viewpoint) + d;
	}
	while (++i < 10)
		if (scene.sources[i].type == 'p')
		{
			s = scene.sources[i];
			if (scene.objects[closest].type == 'p')
				if ((dot(scene.objects[closest].norm, s.position) + d) * plane_vp < 0.)
					s.intensities = 0;
			pl.d = s.position - pn.o;

			obj = get_closest(pl, scene.objects, &dist, scene.cl_lim);
			if (obj >= 0)
			{
				if (scene.objects[obj].negative != 1 && scene.objects[obj].trans > 0)
					modifier = scene.objects[obj].trans;
				if (scene.objects[obj].negative == 1 || scene.objects[obj].trans > 0)
				{
					tmp.o = pl.o + (pl.d)  * dist * 1.000001f ;
					tmp.d = (pl.d - pl.o ) / length(pl.d- pl.o) ;
					tmpdist = dist;
					obj = get_closest(tmp, scene.objects, &dist, scene.cl_lim);
					dist += tmpdist;
				}
			}
			if (obj == -1)
			{
		 		if (dot(pn.d, pl.d) > 0.0f)
					intensities += s.intensities * dot(pn.d, pl.d) / length(pl.d) * modifier;
				if (dot(pn.d, pl.d) < 0.0f && scene.objects[closest].type == 'p')
					intensities -= s.intensities * dot(pn.d, pl.d) / length(pl.d) * modifier;
				if (specular > 0)
				{
					pl.d = pn.d * (2.0f * dot(pn.d, pl.d)) - pl.d;
					if (dot(pl.d, md) > 0.0f)
						intensities += s.intensities * native_powr(dot(pl.d, md) / length(pl.d) / length(md), specular) * modifier ;
				}
				
			}
		}
	return (intensities);
}*/







//добавить функцию (получает параметр L)
float3		get_big_l(t_source s, t_ray pn)
{
	float3 d;

	if (s.type == 'p')
		d = s.position - pn.o;
	else
		d = s.position * (-1);
		//direction
	return (d);
}

//добавить функцию (устанавливает лимитные значение - max и min в зависимости от типа источника)
t_lim		get_cl_lim(t_source s)
{
	t_lim cl_lim;

	if (s.type == 'p')
	{
		cl_lim.max = 1.0f;
		cl_lim.min = 0.001f;
	}
	else
	{
		cl_lim.max = 40000.0f;
		cl_lim.min = 0.001f;
	}
	return (cl_lim);	
}

//добавть функцию (является частью функционала по нахождению степени освещённости,
//включает в себя реализацию изменения тени в зависимости от степени прозрачности)
float			compute_shadow(t_scene scene, t_ray pl)
{
	float		shadow_coef;
	float		dist;
	int			closest_figure;


	

	shadow_coef = 1;
	
	//zero_negatives_arr(param);
	// inter_res_shadow = look_for_intersections(param, param->vec_params.p_big,
	// 	param->vec_params.l_big);
	closest_figure = get_closest(pl, scene.objects, &dist, scene.cl_lim);
	if (scene.objects[closest_figure ].negative == 1)
					return (1.f);

	//direction = param->vec_params.l_big;

	//if (closest_figure != -1)
	//	return (0);

	while  (closest_figure != -1)
	{

		if (scene.objects[closest_figure].refractive == 0)
		{
			shadow_coef = 0;
			return (shadow_coef);
		}

		shadow_coef *= scene.objects[closest_figure].refractive;


	// 	start = vec_sum(inter_res_shadow.start,
	// mult_vector_on_constant(inter_res_shadow.direction, inter_res_shadow.closest_t));

		pl.o += pl.d * dist;

		// zero_negatives_arr(param);
		// inter_res_shadow = look_for_intersections(param, start, direction);

		closest_figure =  get_closest(pl, scene.objects, &dist, scene.cl_lim);
	}
	return (shadow_coef);
}

//заменить предыдущую функцию (включает в себя реализацию разных типов источников света и цвет света)
float3		compute_lighting(t_ray pn, float3 md, t_scene scene, int specular, int closest)
{
	float3		intensities;
	t_source	s;
	t_ray		pl;
	// float		dist;
	int			i = -1;
	float		plane_vp;
	float		d;
	float		shadow_coef;

	intensities.x = 0.0f;
	intensities.y = 0.0f;
	intensities.z = 0.0f;


	pl.o = pn.o;
//	if (scene.objects[closest].type == 'p')
//	{
//		d = -1. * dot(scene.objects[closest].norm, scene.objects[closest].center);
//		plane_vp = dot(scene.objects[closest].norm, scene.viewpoint) + d;
//	}
	while (++i < 10)
	{
		if (scene.sources[i].type == 'p' || scene.sources[i].type == 'a' || scene.sources[i].type == 'd')
		{
			s = scene.sources[i];
			if (s.type == 'a')
				intensities += s.intensities;
			else
			{
					// plane correction
//				if (scene.objects[closest].type == 'p')
//				{
//					if (root2 == INF)
//						scene.objects[closest].norm *= -1;
//					if ((dot(scene.objects[closest].norm, s.position) + d) * plane_vp < 0. && scene.sources[i].type != 'd')
//					{
//						s.intensities.x = 0.0f;
//						s.intensities.y = 0.0f;
//						s.intensities.z = 0.0f;
//					}
//					if ((dot(scene.objects[closest].norm, s.position) + d) *
//					plane_vp < 0. && scene.sources[i].type == 'd')
//					{
//						s.intensities.x = 0.0f;
//						s.intensities.y = 0.0f;
//						s.intensities.z = 0.0f;
//					}
//				}

				// plane correction

				pl.d = get_big_l(s, pn);
				//pl.d = s.position - pn.o;

				scene.cl_lim = get_cl_lim(s);

				shadow_coef = compute_shadow(scene, pl);
				
				if (shadow_coef == 0)
				{
					s.intensities.x = 0.0;
					s.intensities.y = 0.0;
					s.intensities.z = 0.0;
					continue ;
				}

				//compute diffuseness
				if (dot(pn.d, pl.d) > 0.0f)
					intensities += s.intensities * dot(pn.d, pl.d) / length(pl.d) * shadow_coef;
				// plane correction
//				if (dot(pn.d, pl.d) < 0.0f && scene.objects[closest].type == 'p')
//					intensities -= s.intensities * dot(pn.d, pl.d) / length(pl.d) * shadow_coef;
				//compute shine
				if (specular > 0)
				{
					pl.d = pn.d * (2.0f * dot(pn.d, pl.d)) - pl.d;
					if (dot(pl.d, md) < 0.0f) {
						intensities += s.intensities * pow(dot(pl.d, md) / length(pl.d) / length(md), specular) * shadow_coef;
					}
				}
			}
		}
	}
	return (intensities);
}
