#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	finalsize;

	finalsize = 0;
	if (dstsize > 0)
	{
		while (*(src + finalsize) != '\0' && finalsize < dstsize - 1)
		{
			*(dst + finalsize) = *(src + finalsize);
			finalsize++;
		}
		*(dst + finalsize) = '\0';
	}
	return (ft_strlen(src));
}
