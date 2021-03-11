#include "shell.h"

int			is_valid_var_end(char c)
{
	if (c == 0 || c == '\'' || c == ' ' || c == '"' || c == '$')
		return (1);
	return (0);
}

char		*env_get_var(char *var, t_env *env)
{
	size_t	i;
	int		vl;

	i = 0;
	vl = 0;
	while (!is_valid_var_end(var[vl]) || (vl == 0 && var[vl] == '0'))
		vl++;
	while (i < env->n)
	{
		if (ft_strncmp(var, env->envp[i], vl) == 0)
		{
			if (env->envp[i][vl] == '=')
				return (&env->envp[i][vl + 1]);
		}
		i++;
	}
	return (0);
}

void		ft_env(t_env *env)
{
	size_t	i;

	i = 0;
	while (i < env->n)
		ft_putendl_fd(env->envp[i++], 1);
}
