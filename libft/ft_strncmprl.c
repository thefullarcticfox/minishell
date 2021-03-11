#include "libft.h"

int		ft_strncmprl(const char *s1, const char *s2, size_t n)
{
	const unsigned char	*str1;
	const unsigned char	*str2;

	str1 = (const unsigned char*)s1;
	str2 = (const unsigned char*)s2;
	while (n > 0 && (*str1 != '\0' || *str2 != '\0'))
	{
		if (ft_tolower(*str1) != ft_tolower(*str2))
			return (*str1 - *str2);
		str1++;
		str2++;
		n--;
	}
	return (0);
}
