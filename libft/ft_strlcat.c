#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	initdstsize;
	size_t	srcsize;
	size_t	finalsize;

	initdstsize = 0;
	if (dstsize > 0)
	{
		srcsize = 0;
		initdstsize = ft_strlen(dst);
		finalsize = initdstsize;
		while (*(src + srcsize) != '\0' && finalsize < dstsize - 1)
		{
			*(dst + finalsize) = *(src + srcsize);
			finalsize++;
			srcsize++;
		}
		*(dst + finalsize) = '\0';
	}
	if (initdstsize < dstsize)
		return (ft_strlen(src) + initdstsize);
	else
		return (ft_strlen(src) + dstsize);
}
