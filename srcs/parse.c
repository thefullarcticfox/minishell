#include "shell.h"

void		my_what_exec(t_env *env)
{
	g_childpid = -1;
	ft_argvredirscheck(env);
	if (ft_strncmprl(env->argv[0], "cd", 3) == 0)
		ft_cd(env);
	else if (ft_strncmprl(env->argv[0], "pwd", 4) == 0)
		ft_pwd();
	else if (ft_strncmprl(env->argv[0], "echo", 5) == 0)
		ft_echo(env->argv);
	else if (ft_strncmp(env->argv[0], "export", 7) == 0)
		ft_export(env);
	else if (ft_strncmprl(env->argv[0], "env", 4) == 0)
		ft_env(env);
	else if (ft_strncmp(env->argv[0], "exit", 5) == 0)
		ft_exit(env);
	else if (ft_strncmp(env->argv[0], "unset", 6) == 0)
		ft_unset(env);
	else if (ft_strlen(env->argv[0]) != 0)
		ft_runcmd(env);
	else
		g_exitcode = 0;
}

void		parse_line(t_env *env)
{
	g_exitcode = 0;
	if (my_redirect_in(env))
		if (my_redirect_from(env))
			if (env->argc > 0 && env->argv != NULL)
				my_what_exec(env);
}
