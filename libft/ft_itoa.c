#include "libft.h"

static int	ft_unsignint(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

static int	ft_nmlen(int n)
{
	int		len;

	len = 1;
	if (n < 0)
		len++;
	while (n / 10 != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char		*ft_itoa(int n)
{
	int		len;
	char	*array;

	len = ft_nmlen(n);
	if (!(array = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	array[len] = '\0';
	if (n < 0)
		array[0] = '-';
	while (n / 10 != 0)
	{
		array[--len] = ft_unsignint(n % 10) + '0';
		n /= 10;
	}
	array[--len] = ft_unsignint(n % 10) + '0';
	return (array);
}
