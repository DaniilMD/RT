#include "rtv1.h"

void			get_object_parameters_inner(t_cl_object *object, char *str)
{
	if (ft_strstr(str, "center:"))
		object->center = parse_vector(ft_strstr(str, "center:"));
	if (ft_strstr(str, "direction:"))
		object->norm = norm_v(parse_vector(ft_strstr(str, "direction:")));
	if (ft_strstr(str, "color:"))
		object->color = parse_color(ft_strstr(str, "color:"));
	if (ft_strstr(str, "radius:"))
		object->radius = ft_atof(ft_strstr(str, "radius:") + 7);
}

void			compile_cl_inner(t_cl *cl, int i)
{
	char		*log;
	size_t		log_size;

	clGetProgramBuildInfo(cl->programs[i], cl->dev_id,
		CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);
	log = (char *)malloc(log_size);
	clGetProgramBuildInfo(cl->programs[i], cl->dev_id,
		CL_PROGRAM_BUILD_LOG, log_size, log, NULL);
	free(log);
}

void			releasecl(t_cl *cl)
{
	clReleaseMemObject(cl->z_clmem);
	clReleaseMemObject(cl->txt_clmem);
	clReleaseKernel(cl->kernel);
	clReleaseProgram(cl->program);
	clReleaseCommandQueue(cl->command_queue);
	clReleaseContext(cl->context);
}
