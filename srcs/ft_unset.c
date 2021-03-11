#include "shell.h"

static void	my_dell_arg(t_env *env, size_t n)
{
	char	**temp;
	size_t	i;
	size_t	j;

	if (!(temp = (char**)malloc((env->n) * sizeof(char*))))
		exit_status(NULL);
	i = 0;
	j = 0;
	while (i < env->n)
		if (i != n)
			temp[j++] = env->envp[i++];
		else
			free(env->envp[i++]);
	temp[j] = 0;
	free(env->envp);
	env->envp = temp;
	(env->n)--;
}

static int	my_find_var(char *arg, t_env *env)
{
	size_t	i;
	size_t	j;

	i = -1;
	while (++i < env->n)
	{
		j = 0;
		while (env->envp[i][j] && arg[j] && env->envp[i][j] != '=' &&
				env->envp[i][j] == arg[j])
			j++;
		if (env->envp[i][j] == '=' && arg[j] == 0)
			return (i);
	}
	return (-1);
}

void		ft_unset(t_env *env)
{
	int	i;
	int	arg_num;

	i = 0;
	g_exitcode = 0;
	while (env->argv[++i])
	{
		if (u_isvalid(env->argv[i]))
		{
			if ((arg_num = my_find_var(env->argv[i], env)) >= 0)
				my_dell_arg(env, arg_num);
		}
		else
		{
			g_exitcode = 1;
			ft_error("unset", env->argv[i], "not a valid identifier");
		}
	}
}
