#include "shell.h"
#include "get_next_line.h"

static void		my_run_cmd(t_env *env, char *cmd)
{
	int	n;

	n = ft_wordcount(env->pipe);
	if (n == 1)
	{
		if (!(env->argv = ft_splittoargv(cmd, ' ')))
		{
			ft_error(NULL, NULL, strerror(errno));
			free(cmd);
			return ;
		}
		ft_processargv(env);
		ft_countargc(env);
		parse_line(env);
		ft_freeargv(env);
	}
	else
		run_pipes(env, n - 1);
	free(cmd);
}

static void		ft_freepipe(t_env *env)
{
	size_t	i;

	if (env->pipe == NULL)
		return ;
	i = 0;
	while (env->pipe[i] != NULL)
		free(env->pipe[i++]);
	free(env->pipe);
	env->pipe = NULL;
}

static void		ft_splitcommands(t_env *env, char *line)
{
	size_t	i;
	char	**cmds;

	if (line == NULL || !(cmds = ft_splittoargv(line, ';')))
	{
		if (errno != 0)
			ft_error(NULL, NULL, strerror(errno));
		return ;
	}
	i = -1;
	while (cmds[++i] != NULL)
	{
		if (!(env->pipe = ft_splittoargv(cmds[i], '|')))
		{
			if (errno != 0)
				ft_error(0, 0, strerror(errno));
			free(cmds[i]);
		}
		else
			my_run_cmd(env, cmds[i]);
		ft_freepipe(env);
	}
	free(cmds);
}

static void		ft_ctrldhandle(char **line, char *buf)
{
	char	*tmp;

	tmp = *line;
	*line = ft_strjoin(tmp, buf);
	free(buf);
	free(tmp);
}

void			control(t_env *env)
{
	int		gnlres;
	char	*line;
	char	*buf;

	while (1)
	{
		ft_putstr_fd("minishell$ ", 0);
		gnlres = get_next_line(0, &line);
		if (gnlres < 0 || line == NULL)
			exit_status(NULL);
		if (gnlres == 0 && line != NULL && ft_strlen(line) == 0)
		{
			free(line);
			ft_exit(env);
		}
		if (gnlres == 0 && line != NULL && ft_strlen(line) > 0)
		{
			while (line != NULL && ft_strlen(line) > 0 &&
				get_next_line(0, &buf) < 1 && buf != NULL)
				ft_ctrldhandle(&line, buf);
			ft_ctrldhandle(&line, buf);
		}
		ft_splitcommands(env, line);
		free(line);
	}
}
