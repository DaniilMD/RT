#ifndef RTV1_H
# define RTV1_H
# include "SDL.h"
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include "libft.h"
# define C_W 1024
# define C_H 768
# define N_OBJ 10
# define N_SRC 10
# include <OpenCL/opencl.h>

typedef struct			s_cl
{
	char				*source_str;
	size_t				source_size;
	cl_context			context;
	cl_device_id		dev_id;
	cl_platform_id		platform_id;
	cl_program			header[1];
	cl_program			programs[7];
	cl_program			program;
	cl_command_queue	command_queue;
	cl_kernel			kernel;
	cl_mem				z_clmem;
	cl_mem				scene_buf;
	cl_mem				txt_clmem;
}						t_cl;

typedef struct			s_sdl
{
	SDL_Surface			*screen;
	SDL_Window			*window;
	SDL_Renderer		*renderer;
	SDL_Texture			*texture;
	t_cl				cl_inst;
	char				**scenes;
	int					scene_num;
	int					help;
}						t_sdl;

typedef struct			s_lim
{
	float				max;
	float				min;
}						t_lim;

typedef struct			s_matrix
{
	float				m[3][3];
}						t_matrix;

typedef struct			s_cl_object
{
	cl_char				type;
	cl_float			dist;
	cl_float3			center;
	cl_float			radius;
	cl_float3			norm;
	cl_float			alpha;
	cl_int3				color;
	cl_int				specular;
	cl_float			reflective;
	cl_float			transparency;
	cl_int				texture;
	cl_char				textype;
	cl_float2			shift;
	cl_float2			scale;
	cl_float4			slice[4];
	cl_int				slice_side[4];
	cl_int				negative;
	cl_float			refractive;
	cl_float			index_of_refr;
}						t_cl_object;

typedef struct			s_cl_source
{
	cl_float3			position;
	cl_float3			intensities;
	cl_char				type;
}						t_cl_source;

typedef struct			s_scene
{
	t_cl_object			objects[N_OBJ];
	t_cl_source			sources[N_SRC];
	cl_float3			startviewpoint;
	cl_float3			viewpoint;
	t_matrix			rot_matrix;
	t_lim				cl_lim;
	t_lim				tr_lim;
	cl_int				effect;
	cl_int				effect_int;
	cl_float3			cam_angles;
	cl_int				width;
	cl_int				height;
	cl_int				current_scene;
	cl_int				animate;
}						t_scene;

typedef struct			s_controls
{
	t_sdl				sdl;
	t_scene				scene;
}						t_controls;

cl_float3				return_zero_vector(void);
cl_float2				return_zero_2dvector(void);
cl_float4				return_zero_4dvector(void);
cl_int3					return_zero_color(void);
t_matrix				return_eig_rot_m(cl_float3 cam_ang);
cl_float3				parse_vector(char *str);
cl_float2				parse_2dvector(char *str);
cl_float4				parse_4dvector(char *str);
cl_int3					parse_color(char *str);
char					parse_type(char *str);
void					get_slices(t_cl_object *object, char *str0);
void					get_object_parameters(t_cl_object *object, char *str);
char					parse_object_type(char *str);
cl_int3					*rt_cl(t_cl *cl, t_scene scene);
cl_float3				ft_vrot(cl_float3 a, t_matrix rot);
int						construct_scene(char *str, t_scene *scene, t_sdl *sdl);
void					ft_draw(t_sdl sdl, t_scene scene);
void					effect(cl_int4 *z, t_sdl sdl, t_scene scene);
t_cl					initcl(t_sdl *sdl);
int						ft_parse_scene(char *filename, t_scene *scene);
void					controls(t_sdl sdl, t_scene scene);
void					releasecl(t_cl *cl);
void					loading_message(t_sdl *sdl);
void					progress_bar(t_sdl *sdl, float percent);
cl_float3				norm_v(cl_float3 vector);

void					ft_draw_inner_sdl(t_sdl sdl);
void					get_object_parameters_inner(t_cl_object *object, char
*str);
void					compile_cl_inner(t_cl *cl, int i);
void					controls_inner_sdl_scene(t_sdl sdl, t_scene *scene);
void					keyboard_effects_inner(t_sdl sdl, t_scene *scene,
const Uint8 *keystate);
void					keyboard_sdl_scancode_pageup(t_sdl sdl, t_scene *scene);
void					keyboard_sdl_scancode_pagedown(t_sdl sdl, t_scene
*scene);
void					keyboard_sdl_scancode_plus(t_scene *scene);
void					controls_inner_cam(t_sdl *sdl, t_scene *scene,
							SDL_Event event,
const Uint8 *keystate);
void					keyboard_sdl_scancode_h(t_sdl *sdl, t_scene scene);
void					camera_movement(t_sdl sdl, t_scene *scene, SDL_Event
event);
void					camera_rotation(t_sdl sdl, t_scene *scene, SDL_Event
event);
void					keyboard_effects(t_sdl sdl, t_scene *scene, const Uint8
*keystate);
void					make_pixelize(int *c, int n, cl_int4 *z, cl_int4 sum);
void					vector_sum(cl_int4 *z, cl_int4 add);
void					dodge(cl_int4 *front, cl_int4 *back);
void					invert(cl_int4 *z);
void					grayscale(cl_int4 *z, int i);
void					sepia(cl_int4 *z);
void					pixelize(cl_int4 *z, int n);
void					box_blur(cl_int4 *z, int n);
void					vector_div_n(cl_int4 *z, int n);

#endif
