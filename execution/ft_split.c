#include "../header.h"

static int	is_separator(char c, char x)
{
	int		i;

	i = 0;
	if (c == x)
		return (1);
	return (0);
}

static int	count(const char *str, char c)
{
	int		i;
	int		count;

	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		while (str[i] != '\0' && is_separator(str[i], c) == 1)
			i++;
		if (str[i] != '\0')
		{
			count++;
			i++;
		}
		while (str[i] != '\0' && is_separator(str[i], c) == 0)
			i++;
	}
	return (count);
}

static char	*step_one_two(const char *str, char c)
{
	int		length;
	char	*cut_string;
	int		i;

	i = 0;
	while (str[i] != '\0' && is_separator(str[i], c) == 0)
		i++;
	length = i;
	cut_string = (char *)malloc(sizeof(char) * length + 1);
	if (!cut_string)
		return (NULL);
	i = 0;
	while (i < length)
	{
		cut_string[i] = str[i];
		i++;
	}
	cut_string[i] = '\0';
	return (cut_string);
}

static char	**allocate_fail(char **my_str)
{
	int		i;

	i = 0;
	while (my_str[i] != NULL)
	{
		free(my_str[i]);
		i++;
	}
	free(my_str);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**my_str;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	my_str = (char **)malloc(sizeof(char *) * (count(s, c) + 1));
	if (!my_str)
		return (0);
	while (*s != '\0')
	{
		while (*s != '\0' && is_separator(*s, c) == 1)
			s++;
		if (*s != '\0')
		{
			my_str[i] = step_one_two(s, c);
			if (!my_str[i])
				return (allocate_fail(my_str));
			i++;
		}
		while (*s != '\0' && is_separator(*s, c) == 0)
			s++;
	}
	my_str[i] = 0;
	return (my_str);
}
