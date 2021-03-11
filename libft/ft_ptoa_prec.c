#include "libft.h"

/*
** ft_ptoa_prec - pointer address to array with precision.
** Converts a pointer address to a null-terminated string with base 16
** with 0x prefix and stores the result in the array. Chars are lowercase.
** If precision > ptrlen, leading zeroes added after 0x.
** If precision higher than INTMAX-3 then it's truncated to INTMAX-3 to fit.
** Returns array on success. Returns NULL on allocation error.
*/

static int	ft_ptrlen(unsigned long int n, int prec)
{
	int		len;

	len = 1;
	while (n / 16 != 0)
	{
		n /= 16;
		len++;
	}
	if (prec > 2147483644)
		prec = 2147483644;
	if (prec > len)
		len = prec;
	len += 2;
	return (len);
}

char		*ft_ptoa_prec(void *p, int prec)
{
	unsigned long int	n;
	int					i;
	int					len;
	char				*array;

	n = (unsigned long int)p;
	len = ft_ptrlen(n, prec);
	if (!(array = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = 0;
	while (i < len)
		array[i++] = '0';
	array[1] = 'x';
	array[len] = '\0';
	while (n / 16 != 0)
	{
		array[--len] = "0123456789abcdef"[n % 16];
		n /= 16;
	}
	array[--len] = "0123456789abcdef"[n % 16];
	return (array);
}
