#include "shell.h"

void		ft_echo(char **av)
{
	size_t	i;
	int		nl;

	i = 1;
	nl = 1;
	g_exitcode = 0;
	while (av[i] && ft_strncmp(av[i], "-n", 3) == 0)
	{
		nl = 0;
		i++;
	}
	i--;
	while (av[++i])
	{
		ft_putstr_fd(av[i], 1);
		if (av[i + 1] != 0)
			ft_putstr_fd(" ", 1);
	}
	if (nl)
		ft_putstr_fd("\n", 1);
}
