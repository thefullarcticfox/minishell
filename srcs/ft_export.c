#include "shell.h"

static int	my_alloc_envp(t_env *env)
{
	char		**out1;
	size_t		i;

	if (!(out1 = (char**)malloc(sizeof(char*) * (env->n + 2))))
		exit_status(NULL);
	i = -1;
	while (++i < env->n)
		out1[i] = env->envp[i];
	out1[i + 1] = 0;
	free(env->envp);
	env->envp = out1;
	return (i);
}

static void	my_set_var(char *arg, t_env *env)
{
	int		num;

	num = my_alloc_envp(env);
	env->envp[num] = ft_strdup(arg);
	(env->n)++;
}

static void	my_change_var(int envp_num, char *arg, t_env *env)
{
	free(env->envp[envp_num]);
	env->envp[envp_num] = ft_strdup(arg);
}

void		ft_export(t_env *env)
{
	int	i;
	int	j;

	i = 0;
	g_exitcode = 0;
	if (env->argc == 1)
		u_sort_and_print(env);
	else
		while (env->argv[++i])
		{
			j = 0;
			while (env->argv[i][j] > 32 && env->argv[i][j] != '=')
				j++;
			if (u_isvalid(env->argv[i]) && env->argv[i][j] == '=')
				if ((j = u_find_var(env->argv[i], env)) >= 0)
					my_change_var(j, env->argv[i], env);
				else
					my_set_var(env->argv[i], env);
			else if (!(u_isvalid(env->argv[i])))
			{
				ft_error("export", env->argv[i],
						"not a valid identifier");
				g_exitcode = 1;
			}
		}
}
