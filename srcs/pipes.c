#include "shell.h"

static void	my_exec_pcmd(char *cmd, t_env *env)
{
	if (!(env->argv = ft_splittoargv(cmd, ' ')))
	{
		if (errno != 0)
			ft_error(0, 0, strerror(errno));
		free(cmd);
		return ;
	}
	ft_processargv(env);
	ft_countargc(env);
	parse_line(env);
}

static void	my_help_run(int j, t_env *env, int n, int *pfds)
{
	int	i;

	if (j != 0)
		if (dup2(pfds[2 * (j - 1)], 0) < 0)
			exit_status(NULL);
	if (j != n)
		if (dup2(pfds[2 * j + 1], 1) < 0)
			exit_status(NULL);
	i = -1;
	while (++i < 2 * n)
		close(pfds[i]);
	my_exec_pcmd(env->pipe[j], env);
	exit(g_exitcode);
}

static void	my_waitexitstatus(pid_t pid)
{
	int		status;

	status = 0;
	if (waitpid(pid, &status, WUNTRACED) == -1)
		ft_error(NULL, NULL, strerror(errno));
	if (status == 0)
		g_exitcode = 0;
	else if (WEXITSTATUS(status) != 141)
		g_exitcode = WEXITSTATUS(status);
}

static void	my_run_commands(t_env *env, int n, int *pfds)
{
	int		j;
	pid_t	*pids;

	j = -1;
	if (!(pids = (pid_t *)malloc((n + 1) * sizeof(pid_t))))
	{
		ft_error(NULL, NULL, strerror(errno));
		return ;
	}
	while (++j <= n)
	{
		pids[j] = fork();
		if (pids[j] == 0)
			my_help_run(j, env, n, pfds);
		else if (pids[j] < 0)
			exit_status(NULL);
	}
	j = -1;
	while (++j < 2 * n)
		close(pfds[j]);
	j = -1;
	while (++j <= n)
		my_waitexitstatus(pids[j]);
	free(pids);
}

void		run_pipes(t_env *env, int n)
{
	int	*pfds;
	int	i;

	i = 0;
	if (!(pfds = (int*)malloc(2 * n * sizeof(int))))
	{
		ft_error(0, 0, strerror(errno));
		return ;
	}
	while (i < n)
		if (pipe(pfds + 2 * i++) < 0)
		{
			ft_error(0, 0, strerror(errno));
			return ;
		}
	my_run_commands(env, n, pfds);
	free(pfds);
}
