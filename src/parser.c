#include "rtv1.h"

void			parse_objects(t_cl_object *objects, char *str)
{
	char	*end;
	int		n;

	n = 0;
	while ((str = ft_strstr(str, "object:")) && n < N_OBJ)
	{
		str += 7;
		while (*str == ' ' || *str == '\n')
			str++;
		if (*str != '{' || !(end = ft_strstr(str, "}")))
			return ;
		*end = '\0';
		if (!ft_strstr(str, "plane") && !ft_strstr(str, "sphere") && \
				!ft_strstr(str, "cyl") && !ft_strstr(str, "cone"))
		{
			*end = '}';
			continue ;
		}
		objects[n].type = parse_object_type(str);
		get_object_parameters(&(objects[n]), str);
		++n;
		*end = '}';
	}
}

void			parse_sources(t_cl_source *sources, char *str)
{
	int			k;

	k = 0;
	while (ft_strstr(str, "light:"))
	{
		str = ft_strstr(str, "light:") + 1;
		if (!ft_strstr(str, "type:"))
			continue ;
		sources[k].type = parse_type(ft_strstr(str, "type:") \
												+ ft_strlen("type:"));
		if (ft_strstr(str, "position:"))
			sources[k].position = parse_vector(ft_strstr(str, "position:") +
					ft_strlen("position:"));
		if (ft_strstr(str, "intensities:"))
			sources[k].intensities = parse_vector(ft_strstr(str,
		"intensities:") + ft_strlen("intensities:"));
		++(k);
		if (k >= N_SRC)
			break ;
	}
}

void			parse_camera(cl_float3 *vp, cl_float3 *angles, t_matrix *rot,
					char *str)
{
	char		*end;

	if (!(str = ft_strstr(str, "camera")))
		return ;
	if (!(str = ft_strstr(str, "{")))
		return ;
	end = ft_strstr(str, "}");
	*end = '\0';
	if (ft_strstr(str, "camera_angles:"))
		*angles = parse_vector(ft_strstr(str, "camera_angles:"));
	else
		*angles = return_zero_vector();
	*rot = return_eig_rot_m(*angles);
	if (ft_strstr(str, "viewpoint:"))
		*vp = parse_vector(ft_strstr(str, "viewpoint:"));
}

void			zero_objects_and_sources(t_cl_object *objects, \
t_cl_source *sources)
{
	int			i;

	i = -1;
	while (++i < N_OBJ)
		ft_memset(&(objects[i]), 0, sizeof(objects[i]));
	i = -1;
	while (++i < N_SRC)
		ft_memset(&(sources[i]), 0, sizeof(sources[i]));
}

int				ft_parse_scene(char *filename, t_scene *scene)
{
	int			fd;
	int			out;
	char		buffer[100000];

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (1);
	zero_objects_and_sources(scene->objects, scene->sources);
	out = read(fd, buffer, 100000);
	buffer[out] = '\0';
	parse_objects(scene->objects, buffer);
	parse_sources(scene->sources, buffer);
	scene->animate = 0;
	if (ft_strstr(buffer, "animate"))
		scene->animate = 1;
	parse_camera(&(scene->viewpoint), &(scene->cam_angles), \
								&(scene->rot_matrix), buffer);
	close(fd);
	fd = -1;
	while (++fd < N_OBJ)
		if (scene->objects[fd].type != 0)
			break ;
	if (fd == N_OBJ)
		return (1);
	return (0);
}
