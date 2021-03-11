#include "shell.h"

void			ft_countargc(t_env *env)
{
	int		i;

	if (env->argv == NULL)
		return ;
	i = 0;
	while (env->argv[i])
		i++;
	env->argc = i;
}

char			*ft_bracketredirs(char *arg)
{
	if (ft_strncmp(arg, "\">>\"", 5) == 0 ||
		ft_strncmp(arg, "\'>>\'", 5) == 0 ||
		ft_strncmp(arg, "\\>\\>", 5) == 0)
		return (ft_strdup(">>\n"));
	if (ft_strncmp(arg, "\">\"", 4) == 0 ||
		ft_strncmp(arg, "\'>\'", 4) == 0 ||
		ft_strncmp(arg, "\\>", 3) == 0)
		return (ft_strdup(">\n"));
	if (ft_strncmp(arg, "\"<\"", 4) == 0 ||
		ft_strncmp(arg, "\'<\'", 4) == 0 ||
		ft_strncmp(arg, "\\<", 3) == 0)
		return (ft_strdup("<\n"));
	return (NULL);
}

char			*ft_redirnl(char *arg)
{
	if (arg)
	{
		if (ft_strncmp(arg, ">\n", 3) == 0)
			return (">");
		else if (ft_strncmp(arg, ">>\n", 4) == 0)
			return (">>");
		else if (ft_strncmp(arg, "<\n", 3) == 0)
			return ("<");
	}
	return (arg);
}

void			ft_argvredirscheck(t_env *env)
{
	size_t	i;
	char	*tmp;

	if (env->argv == NULL)
		return ;
	i = -1;
	while (env->argv[++i] != NULL)
	{
		if (ft_strncmp(env->argv[i], ">\n", 3) == 0 ||
			ft_strncmp(env->argv[i], ">>\n", 4) == 0 ||
			ft_strncmp(env->argv[i], "<\n", 3) == 0)
		{
			if (!(tmp = ft_strdup(ft_redirnl(env->argv[i]))))
				return ;
			free(env->argv[i]);
			env->argv[i] = tmp;
		}
	}
}
