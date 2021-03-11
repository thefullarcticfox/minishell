#include "libft.h"

/*
** ft_itoa_prec - int to array with precision.
** Converts an integer value to a null-terminated string
** with specified precision and stores the result in the array.
** If precision > numlen, leading zeroes added.
** If precision higher than INTMAX-2 then it's truncated to INTMAX-2 to fit.
** Returns array on success. Returns NULL on alloc error.
*/

static int	ft_unsignint(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

static int	ft_nmlen(int n, int prec)
{
	int		len;

	len = 1;
	while (n / 10 != 0)
	{
		n /= 10;
		len++;
	}
	if (prec > 2147483645)
		prec = 2147483645;
	if (prec > len)
		len = prec;
	return (len);
}

char		*ft_itoa_prec(int n, int prec)
{
	int		i;
	int		len;
	char	*array;

	len = ft_nmlen(n, prec);
	if (n < 0)
		len++;
	if (!(array = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = 0;
	while (i < len)
		array[i++] = '0';
	if (n < 0)
		array[0] = '-';
	array[len] = '\0';
	while (n / 10 != 0)
	{
		array[--len] = ft_unsignint(n % 10) + '0';
		n /= 10;
	}
	array[--len] = ft_unsignint(n % 10) + '0';
	return (array);
}
