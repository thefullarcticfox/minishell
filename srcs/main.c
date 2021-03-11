#include "shell.h"

static void		ft_envpcpy(t_env *e, char **envp)
{
	char	*eline;
	char	*tmp;

	e->n = 0;
	if (!(eline = ft_strdup("")))
		exit_status(NULL);
	while (envp[e->n])
	{
		tmp = eline;
		eline = ft_strjoin(eline, envp[e->n]);
		free(tmp);
		if (!eline)
			exit_status(NULL);
		tmp = eline;
		eline = ft_strjoin(eline, "\n");
		free(tmp);
		if (!eline)
			exit_status(NULL);
		e->n++;
	}
	e->envp = ft_split(eline, '\n');
	free(eline);
	if (!e->envp)
		exit_status(NULL);
}

int				g_exitcode;
pid_t			g_childpid;

int				main(int argc, char **argv, char **envp)
{
	t_env	env;

	(void)argc;
	(void)argv;
	g_exitcode = 0;
	g_childpid = -1;
	ft_bzero(&env, sizeof(t_env));
	ft_envpcpy(&env, envp);
	ft_signal();
	control(&env);
	return (0);
}
