#include "libft.h"

static char		**free_mem(char **str)
{
	char **tmp;

	tmp = str;
	while (*str != NULL)
	{
		free(*str);
		str++;
	}
	free(tmp);
	return (NULL);
}

static char		**space_creator(char const *s, char **str, char c)
{
	int i;
	int z;
	int letters;
	int k;

	i = -1;
	z = 0;
	while (s[++i] != '\0')
		if (s[i] != c)
		{
			letters = 0;
			k = i;
			while (s[i++] != c && s[i] != '\0')
				letters++;
			i--;
			*(str + z) = (char*)malloc(sizeof(char) * (letters + 1));
			if (!(*(str + z)))
				return (free_mem(str));
			letters = 0;
			while (s[k] != c && s[k] != '\0')
				str[z][letters++] = s[k++];
			str[z++][letters] = '\0';
		}
	return (str);
}

char			**ft_strsplit(char const *s, char c)
{
	int		i;
	char	**str;
	int		words;

	i = 1;
	words = 0;
	if (!s)
		return (NULL);
	if (s[0] != c && s[0] != '\0')
		words++;
	while (s[i] != '\0')
	{
		if (s[i - 1] == c && s[i] != c)
			words++;
		i++;
	}
	str = (char**)malloc(sizeof(char*) * (words + 1));
	if (!str)
		return (NULL);
	str[words] = NULL;
	str = space_creator(s, str, c);
	return (str);
}
