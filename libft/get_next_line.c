#include "libft.h"

static int	line_runner(char **line, char **extra_line, int reader)
{
	size_t	i;
	char	*tmp;

	i = 0;
	if (!*extra_line)
		return (0);
	while ((*extra_line)[i] != '\0')
	{
		if ((*extra_line)[i] == '\n')
		{
			*line = ft_strsub(*extra_line, 0, i);
			tmp = ft_strdup(*extra_line + i + 1);
			ft_strdel(extra_line);
			*extra_line = tmp;
			return (1);
		}
		i++;
	}
	if (ft_strlen(*extra_line) && reader == 0)
	{
		*line = ft_strdup(*extra_line);
		ft_strdel(extra_line);
		return (1);
	}
	return (0);
}

int			get_next_line(const int fd, char **line)
{
	char		buff[BUFF_SIZE + 1];
	int			reader;
	static char	*extra_line[256];
	char		*tmp;

	if (fd < 0 || !line)
		return (-1);
	while ((reader = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[reader] = '\0';
		if (!extra_line[fd])
			extra_line[fd] = ft_strnew(0);
		tmp = ft_strjoin(extra_line[fd], buff);
		free(extra_line[fd]);
		extra_line[fd] = tmp;
		if (ft_strchr(extra_line[fd], '\n'))
			break ;
	}
	if (reader < 0)
		return (-1);
	return (line_runner(line, &extra_line[fd], reader));
}
