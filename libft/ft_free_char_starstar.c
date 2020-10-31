#include "libft.h"

void		free_char_starstar(char **lines)
{
	int	i;

	i = 0;
	while (lines[i] != 0)
	{
		free(lines[i]);
		i++;
	}
	free(lines);
}
