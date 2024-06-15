#include "../header.h"

char	*ft_strdup(const char *src)
{
	char	*duplcate;
	int		i;
	size_t	length_src;

	length_src = ft_strlen(src);
	duplcate = (char *)malloc(sizeof (char) * length_src + 1);
	if (!duplcate)
		return (0);
	i = 0;
	while (src[i] != '\0')
	{
		duplcate[i] = src[i];
		i++;
	}
	duplcate[i] = '\0';
	return (duplcate);
}
