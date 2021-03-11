#include "libft.h"

static int	ft_isinset(char const *s1, char const *set)
{
	int		i;

	i = 0;
	while (set[i] != '\0')
	{
		if (*s1 == set[i])
			return (1);
		i++;
	}
	return (0);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	first;
	size_t	last;

	if (s1 == NULL || set == NULL)
		return (NULL);
	first = 0;
	last = ft_strlen(s1);
	if (ft_strlen(set) > 0)
	{
		while (ft_isinset(s1 + last - 1, set) && last > 0)
			last--;
		while (ft_isinset(s1 + first, set) && last != 0)
			first++;
	}
	if (!(str = (char *)malloc(sizeof(char) * (last - first + 1))))
		return (NULL);
	ft_strlcpy(str, s1 + first, last - first + 1);
	return (str);
}
