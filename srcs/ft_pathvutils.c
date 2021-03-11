#include "shell.h"

char			*ft_gethome(t_env *env, char *str)
{
	char	*tmp;

	if (env_get_var("HOME", env) != NULL &&
		(ft_strncmp(str, "~", 2) == 0 ||
		ft_strncmp(str, "~/", 2) == 0))
	{
		tmp = str;
		str = ft_strjoin(env_get_var("HOME", env), tmp + 1);
		free(tmp);
	}
	return (str);
}

static void		ft_freepvonerror(t_env *env, size_t i)
{
	size_t	argn;

	ft_error(NULL, NULL, strerror(errno));
	if (!env->pathv)
		return ;
	argn = 0;
	while (argn < i)
		free(env->pathv[argn++]);
	while (env->pathv[++argn])
		free(env->pathv[argn]);
	free(env->pathv);
	env->pathv = NULL;
}

void			ft_freepathv(t_env *env)
{
	size_t	i;

	if (env->pathv == NULL)
		return ;
	i = 0;
	while (env->pathv[i] != NULL)
		free(env->pathv[i++]);
	free(env->pathv);
	env->pathv = NULL;
}

void			ft_getpathv(t_env *env)
{
	size_t	i;
	char	*pathstr;

	if (!(pathstr = env_get_var("PATH", env)))
		return ;
	if (!(env->pathv = ft_split(pathstr, ':')))
		ft_error(NULL, NULL, strerror(errno));
	i = -1;
	while (env->pathv != NULL && env->pathv[++i])
	{
		if (!(env->pathv[i] = ft_gethome(env, env->pathv[i])))
		{
			ft_freepvonerror(env, i);
			return ;
		}
		pathstr = ft_strjoin(env->pathv[i], "/");
		free(env->pathv[i]);
		env->pathv[i] = pathstr;
		if (env->pathv[i] == NULL)
		{
			ft_freepvonerror(env, i);
			return ;
		}
	}
}
