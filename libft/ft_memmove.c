#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dest;
	unsigned char	*source;

	if (src < dst)
	{
		dest = (unsigned char*)dst;
		source = (unsigned char*)src;
		while (len-- > 0)
			*(dest + len) = *(source + len);
	}
	if (src > dst)
		ft_memcpy(dst, src, len);
	return (dst);
}
