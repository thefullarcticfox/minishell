#include "shell.h"

static void		ft_freeavonerror(t_env *env, size_t i)
{
	size_t	argn;

	ft_error(NULL, NULL, strerror(errno));
	if (!env->argv)
		return ;
	argn = 0;
	while (argn < i)
		free(env->argv[argn++]);
	while (env->argv[++argn])
		free(env->argv[argn]);
	free(env->argv);
	env->argv = NULL;
}

static void		ft_closingbracket(char **res, char **arg, char **tmp)
{
	char	*tmpres;

	if (**tmp)
	{
		**tmp = 0;
		tmpres = *res;
		*res = ft_strjoin(*res, *arg);
		free(tmpres);
		++(*tmp);
		*arg = *tmp;
	}
}

static void		ft_brackets(t_env *env, char **res, char **arg, char **tmp)
{
	char	*tmpres;

	env->dquote = 0;
	if (**tmp == '\"')
		env->dquote = 1;
	**tmp = 0;
	tmpres = *res;
	*res = ft_strjoin(*res, *arg);
	free(tmpres);
	if ((*tmp)[1])
		(*tmp)++;
	*arg = *tmp;
	if (env->dquote && **arg)
		while (**tmp && **tmp != '\"')
			ft_processvars(env, res, arg, tmp);
	else
		while (**tmp && **tmp != '\'')
			(*tmp)++;
	ft_closingbracket(res, arg, tmp);
}

static char		*ft_processarg(t_env *env, char *arg)
{
	char	*res;
	char	*tmpres;
	char	*tmp;

	if ((res = ft_bracketredirs(arg)) != NULL)
		return (res);
	res = ft_strdup("");
	tmp = arg;
	while (*tmp && res)
	{
		env->dquote = 0;
		if (*tmp == '\'' || *tmp == '\"')
			ft_brackets(env, &res, &arg, &tmp);
		else
			ft_processvars(env, &res, &arg, &tmp);
	}
	tmpres = res;
	res = ft_strjoin(res, arg);
	free(tmpres);
	return (res);
}

void			ft_processargv(t_env *env)
{
	size_t	i;
	char	*tmp;

	i = -1;
	while (env->argv != NULL && env->argv[++i] != NULL)
	{
		if (!(env->argv[i] = ft_gethome(env, env->argv[i])))
		{
			ft_freeavonerror(env, i);
			return ;
		}
		tmp = ft_processarg(env, env->argv[i]);
		free(env->argv[i]);
		env->argv[i] = tmp;
		if (env->argv[i] == NULL)
		{
			ft_freeavonerror(env, i);
			return ;
		}
	}
}
