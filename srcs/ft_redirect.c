#include "shell.h"

static int	ft_openredirin(t_env *env, int i)
{
	int fd;

	if (ft_issyntaxerror(env->argv[i + 1]))
		return (ft_syntaxerrorprint(-1, env->argv[i + 1]));
	if (ft_strncmp(env->argv[i], ">>", 3) == 0)
		fd = open(ft_redirnl(env->argv[i + 1]),
			O_RDWR | O_APPEND | O_CREAT, 0644);
	else
		fd = open(ft_redirnl(env->argv[i + 1]),
			O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (fd < 0)
	{
		ft_error(NULL, ft_redirnl(env->argv[i + 1]), strerror(errno));
		g_exitcode = 1;
	}
	return (fd);
}

int			my_redirect_in(t_env *env)
{
	int	i;
	int	fd;
	int	outcpy;

	i = -1;
	while (++i < env->argc)
		if ((ft_strncmp(env->argv[i], ">", 2) == 0 ||
			ft_strncmp(env->argv[i], ">>", 3) == 0))
		{
			if ((fd = ft_openredirin(env, i)) < 0)
				return (0);
			outcpy = dup(0);
			close(1);
			dup(fd);
			env->argv = ft_delstr(env->argv, i, 2);
			env->argc -= 2;
			if (env->argc > 0 && env->argv)
				parse_line(env);
			close(fd);
			dup2(outcpy, 1);
			return (0);
		}
	return (1);
}

static int	my_utils_redirect_from(t_env *env, int i, int fd)
{
	int	outcpy;

	outcpy = dup(0);
	close(0);
	dup(fd);
	env->argv = ft_delstr(env->argv, i, 2);
	env->argc -= 2;
	if (env->argc > 0 && env->argv)
		my_what_exec(env);
	close(fd);
	dup2(outcpy, 0);
	return (0);
}

int			my_redirect_from(t_env *env)
{
	int	i;
	int	fd;

	i = -1;
	while (++i < env->argc)
		if (ft_strncmp(env->argv[i], "<", 2) == 0)
		{
			if (ft_issyntaxerror(env->argv[i + 1]))
				return (ft_syntaxerrorprint(0, env->argv[i + 1]));
			if (ft_wordcount(&(env->argv[i + 1])) > 1)
			{
				env->argv = ft_delstr(env->argv, i, 2);
				env->argc -= 2;
				parse_line(env);
				return (0);
			}
			if ((fd = open(ft_redirnl(env->argv[i + 1]), O_RDONLY)) < 0)
			{
				g_exitcode = 1;
				ft_error(ft_redirnl(env->argv[i + 1]), 0, strerror(errno));
				return (0);
			}
			return (my_utils_redirect_from(env, i, fd));
		}
	return (1);
}
