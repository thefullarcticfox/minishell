#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*str;
	size_t			ssize;

	i = 0;
	if (s == NULL)
		return (NULL);
	ssize = ft_strlen(s);
	if (start > ssize)
		start = ssize;
	if (len > ssize - start)
		len = ssize - start;
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (s[start + i] != '\0' && i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	if (i == len || str[start + i] == '\0')
		str[i] = '\0';
	return (str);
}
