#include "shell.h"

void			ft_cd(t_env *env)
{
	int		errored;
	DIR		*dir;
	char	*path;

	errored = 0;
	g_exitcode = 0;
	if (env->argc > 1)
		path = env->argv[1];
	else
		path = env_get_var("HOME", env);
	if (path == NULL)
		return ;
	dir = opendir(path);
	if (dir != NULL)
	{
		if (chdir(path) < 0)
			errored = 1;
		if (closedir(dir) < 0)
			errored = 1;
	}
	else
		errored = 1;
	if (errored)
		ft_error("cd", path, strerror(errno));
	g_exitcode = errored;
}
