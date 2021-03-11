#include "shell.h"

static int	ft_processexitarg(char *arg)
{
	int		i;

	if (*arg == 0)
		return (1);
	i = 0;
	if (*arg == '-' || *arg == '+')
		i++;
	if (ft_strnumlen(arg + i) > 19 || !ft_isdigit(*(arg + i)))
		return (0);
	while (*(arg + i))
	{
		if (!ft_isdigit(*(arg + i)))
			return (0);
		i++;
	}
	return (1);
}

void		ft_exit(t_env *env)
{
	ft_putendl_fd("exit", 0);
	if (env == NULL)
		exit(-1);
	if (env->argv == NULL || env->argc < 2)
		exit(g_exitcode);
	if (ft_processexitarg(env->argv[1]) && env->argc < 3)
	{
		g_exitcode = ft_atoi(env->argv[1]);
		ft_freeargv(env);
		exit(g_exitcode);
	}
	else if (ft_processexitarg(env->argv[1]) && env->argc > 2)
	{
		ft_error("exit", NULL, "too many arguments");
		g_exitcode = 1;
	}
	else
	{
		ft_error("exit", env->argv[1], "numeric argument required");
		ft_freeargv(env);
		exit(-1);
	}
}

void		exit_status(char *line)
{
	if (line == NULL)
	{
		ft_error(NULL, NULL, strerror(errno));
		exit(errno);
	}
	else
	{
		ft_error(NULL, NULL, line);
		exit(1);
	}
}
