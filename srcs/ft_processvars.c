#include "shell.h"

static char		*ft_getenvstr(t_env *env, char **tmp)
{
	char	*envar;
	char	*envalue;
	size_t	varend;

	varend = 0;
	if (ft_isdigit((*tmp)[varend]))
		varend++;
	else if (ft_isalpha((*tmp)[varend]))
		while (ft_isalpha((*tmp)[varend]) || ft_isdigit((*tmp)[varend]))
			varend++;
	envar = ft_substr(*tmp, 0, varend);
	envalue = env_get_var(envar, env);
	free(envar);
	(*tmp) += varend;
	if (!envalue)
		return ("");
	return (envalue);
}

static void		ft_varjoin(t_env *env, char **res, char **tmp)
{
	char	*envstr;
	char	*tmpres;

	(*tmp)++;
	if (**tmp == '?' || **tmp == '0')
	{
		if (**tmp == '?')
			envstr = ft_itoa(g_exitcode);
		else
			envstr = ft_strdup("minishell");
		(*tmp)++;
		tmpres = *res;
		*res = ft_strjoin(*res, envstr);
		free(tmpres);
		free(envstr);
	}
	else
	{
		envstr = ft_getenvstr(env, tmp);
		tmpres = *res;
		*res = ft_strjoin(*res, envstr);
		free(tmpres);
	}
}

static void		ft_bslash(char **res, char **arg, char **tmp, char q)
{
	char	*tmpres;
	char	qstr[2];

	qstr[0] = q;
	qstr[1] = '\0';
	**tmp = 0;
	tmpres = *res;
	*res = ft_strjoin(*res, *arg);
	free(tmpres);
	tmpres = *res;
	*res = ft_strjoin(*res, qstr);
	free(tmpres);
	(*tmp) += 2;
	*arg = *tmp;
}

void			ft_processvars(t_env *env, char **res, char **arg, char **tmp)
{
	char	*tmpres;

	if (**tmp == '$' && (*tmp)[1] != '\\' && (*tmp)[1] != 0 &&
		!((*tmp)[1] == '\"' && env->dquote))
	{
		**tmp = 0;
		tmpres = *res;
		*res = ft_strjoin(*res, *arg);
		free(tmpres);
		ft_varjoin(env, res, tmp);
		*arg = *tmp;
	}
	else if ((*tmp)[0] == '\\' && (*tmp)[1] == '\\')
		ft_bslash(res, arg, tmp, (*tmp)[1]);
	else if ((*tmp)[0] == '\\' && (*tmp)[1] == '\"')
		ft_bslash(res, arg, tmp, (*tmp)[1]);
	else if ((*tmp)[0] == '\\' && !(env->dquote))
		ft_bslash(res, arg, tmp, (*tmp)[1]);
	else
		(*tmp)++;
}
