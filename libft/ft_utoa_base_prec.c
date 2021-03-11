#include "libft.h"

/*
** ft_utoa_base_prec - unsigned int to array based with precision.
** Converts an unsigned integer value to a null-terminated string
** using the specified base and stores the result in the array.
** Valid base between 2 and 16. If base > 10 => chars are lowercase.
** If precision > unumlen, leading zeroes added.
** If precision higher than INTMAX-1 then it's truncated to INTMAX-1 to fit.
** Returns array on success. Returns NULL on alloc error or invalid base.
*/

static int	ft_unumlen_base(unsigned int n, int base, int prec)
{
	int		len;

	len = 1;
	while (n / base != 0)
	{
		n /= base;
		len++;
	}
	if (prec > 2147483646)
		prec = 2147483646;
	if (prec > len)
		len = prec;
	return (len);
}

char		*ft_utoa_base_prec(unsigned int n, int base, int prec)
{
	int		i;
	int		len;
	char	*array;

	if (base < 2 || base > 16)
		return (NULL);
	len = ft_unumlen_base(n, base, prec);
	if (!(array = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = 0;
	while (i < len)
		array[i++] = '0';
	array[len] = '\0';
	while (n / base != 0)
	{
		array[--len] = "0123456789abcdef"[n % base];
		n /= base;
	}
	array[--len] = "0123456789abcdef"[n % base];
	return (array);
}
