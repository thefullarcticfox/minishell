#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char		*mem;

	mem = (const unsigned char*)s;
	while (n-- > 0)
	{
		if (*mem == (unsigned char)c)
			return ((void*)mem);
		mem++;
	}
	return (NULL);
}
