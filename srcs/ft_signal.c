#include "shell.h"

static void		ft_sigint(int sig)
{
	if (g_childpid != -1)
	{
		if (kill(g_childpid, sig) < 0)
			ft_error(NULL, NULL, strerror(errno));
	}
	else
	{
		ft_putstr_fd("\b\b  \b\b\n", 0);
		ft_putstr_fd("minishell$ ", 0);
		g_exitcode = 1;
	}
}

static void		ft_sighandler(int sig)
{
	if (sig == SIGINT)
		ft_sigint(sig);
	else if (sig == SIGQUIT)
	{
		if (g_childpid != -1)
		{
			if (kill(g_childpid, sig) < 0)
				ft_error(NULL, NULL, strerror(errno));
		}
		else
			ft_putstr_fd("\b\b  \b\b", 0);
	}
}

void			ft_signal(void)
{
	if ((signal(SIGINT, ft_sighandler)) == SIG_ERR)
		ft_error(NULL, NULL, strerror(errno));
	if ((signal(SIGQUIT, ft_sighandler)) == SIG_ERR)
		ft_error(NULL, NULL, strerror(errno));
}
