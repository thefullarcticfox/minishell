#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*strcp;
	size_t	size;

	size = ft_strlen(s1);
	if (!(strcp = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	return ((char *)ft_memcpy(strcp, s1, size + 1));
}
