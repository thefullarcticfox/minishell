#include "libft.h"

int		ft_iputstr_fd(char *s, int fd)
{
	if (s == 0)
		return (-1);
	return (write(fd, s, ft_strlen(s)));
}
