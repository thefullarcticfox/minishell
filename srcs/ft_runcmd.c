#include "shell.h"
#include <stdio.h>

static int		ft_findinpath(t_env *env)
{
	size_t			i;
	char			*path;
	struct stat		s_fst;

	ft_getpathv(env);
	if ((env->argv[0][0] == '.' || env->argv[0][0] == '/') ||
		!(env->pathv))
		return (-1);
	i = -1;
	while (env->pathv[++i] != NULL)
	{
		path = ft_strjoin(env->pathv[i], env->argv[0]);
		if (stat(path, &s_fst) == 0 && s_fst.st_mode & S_IXUSR)
		{
			free(env->argv[0]);
			env->argv[0] = path;
			return (1);
		}
		else
		{
			errno = 0;
			free(path);
		}
	}
	return (0);
}

static int		ft_processcmd(t_env *env)
{
	struct stat		s_fst;

	if (ft_findinpath(env) == 0)
	{
		ft_error(env->argv[0], NULL, "command not found");
		g_exitcode = 127;
		ft_freepathv(env);
		return (0);
	}
	ft_freepathv(env);
	if (stat(env->argv[0], &s_fst) != 0)
	{
		ft_error(env->argv[0], NULL, "No such file or directory");
		g_exitcode = 127;
		return (0);
	}
	if (S_ISDIR(s_fst.st_mode))
	{
		ft_error(env->argv[0], NULL, "is a directory");
		g_exitcode = 126;
		return (0);
	}
	return (1);
}

void			ft_runcmd(t_env *env)
{
	int		status;

	if (!ft_processcmd(env))
		return ;
	g_childpid = fork();
	if (g_childpid == 0)
	{
		if (execve(env->argv[0], env->argv, env->envp) == -1)
		{
			ft_error(env->argv[0], NULL, strerror(errno));
			g_childpid = -1;
			exit(126);
		}
	}
	else if (g_childpid > 0)
	{
		if (waitpid(g_childpid, &status, WUNTRACED) == -1)
			ft_error(env->argv[0], NULL, strerror(errno));
		g_exitcode = WEXITSTATUS(status);
		ft_sigprint(status);
	}
	else if (g_childpid < 0)
		ft_error(env->argv[0], NULL, strerror(errno));
	g_childpid = -1;
}
