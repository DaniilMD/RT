/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_trace.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwisp <fwisp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/30 20:53:11 by fwisp             #+#    #+#             */
/*   Updated: 2020/08/30 20:54:06 by fwisp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_TRACE_H
# define RAY_TRACE_H
# define INF 4000001.0f
# define SLICE_UP 1
# define SLICE_DOWN 2
# define SAME_SIDE 1
# define DIFF_SIDE 0

typedef struct	s_lim
{
	float		max;
	float		min;
}				t_lim;

typedef struct	s_ray
{
	float3		o;
	float3		d;
}				t_ray;

typedef struct	s_object
{
	char		type;
	float		dist;
	float3		center;
	float		radius;
	float3		norm;
	float		alpha;

	int3		color;
	int			specular;
	float		reflective;
	float		trans;
	int			texture;
	char		textype;
	float2		shift;
	float2		scale;
	float4		slice[4];
	int			slice_side[4];
	int			negative;
	float		refractive;
	float		index_of_refr;
}				t_object;

typedef struct	s_source
{
	float3		position;
	float3		intensities;
	char		type;
}				t_source;

typedef struct	s_roots
{
	float	root1;
	float	root2;
}				t_roots;

typedef struct	s_matrix
{
	float		m[3][3];
}				t_matrix;

typedef struct	s_scene
{
	t_object	objects[10];
	t_source	sources[10];
	float3		startviewpoint;
	float3		viewpoint;
	t_matrix	rot_matrix;
	t_lim		cl_lim;
	t_lim		tr_lim;
	int			effect;
	int			effect_int;
	float3		cam_angles;
	int			width;
	int			height;
	int			current_scene;
	int			animate;
}				t_scene;

int				get_closest(t_ray od, t_object *objects, float *dist, t_lim
lim);
int4			ft_trace_ray(t_ray od, t_lim lim, t_scene scene, int depth);
float3			ft_vrot(float3 a, t_matrix rot);
float3			ft_canvas_to_viewport(int x, int y, int width, int height);
t_ray			obj_refl(t_ray od, t_ray pr, int closest, t_scene scene);
t_ray			new_pr(t_ray od, t_object obj, float dist);
float3			apply_bump(t_ray od, t_object obj, float dist);
float3			obj_col(t_ray pr, t_object obj);
t_roots			ft_intersect_ray_obj(float3 o, float3 d, t_object obj);
float3			compute_lighting(t_ray pn, float3 md, t_scene scene, int
specular, int closest);
t_roots			intersect_slice(t_object obj, float3 start, float3 direction,
int i, t_roots *sqr_eq);
void			slicer(t_object obj, t_roots *sqr_eq, float3 start, float3
direction);
float3			gtexture(t_object obj, float3 pr, float3 o);
float3			get_big_l(t_source s, t_ray pn);
t_lim			get_cl_lim(t_source s);
float			compute_shadow(t_scene scene, t_ray pl);
t_ray			obj_refr(t_ray od, t_ray pr, int closest, t_scene scene);
float			lerp(float a0, float a1, float w);
float			dotgridgradient(int ix, int iy, float x, float y);
float			perlin(float x, float y);

#endif
