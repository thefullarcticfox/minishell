#include "libft.h"

size_t		ft_strnumlen(const char *str)
{
	size_t	len;

	len = 0;
	while (*str != '\0' && *str == '0')
		str++;
	while (ft_isdigit(*(str + len)))
		len++;
	return (len);
}

int			ft_atoi(const char *str)
{
	unsigned long long	number;
	int					sign;
	size_t				nmlen;

	number = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	nmlen = ft_strnumlen(str);
	while (ft_isdigit(*str))
	{
		number = number * 10 + (*str - '0');
		if ((nmlen > 19 || number > 9223372036854775807) && sign > 0)
			return (-1);
		if ((nmlen > 19 || number > 9223372036854775807) && sign < 0)
			return (0);
		str++;
	}
	return ((int)number * sign);
}
