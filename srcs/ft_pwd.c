#include "shell.h"

void	ft_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		ft_error("pwd", NULL, strerror(errno));
		g_exitcode = 1;
		return ;
	}
	ft_putendl_fd(cwd, 1);
	free(cwd);
	g_exitcode = 0;
}
