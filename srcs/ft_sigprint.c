#include "shell.h"

static void		ft_sigprint1(int s)
{
	if (s == SIGHUP)
		ft_putstr_fd("Hangup: ", 1);
	else if (s == SIGINT)
		ft_putstr_fd(NULL, 1);
	else if (s == SIGQUIT)
		ft_putstr_fd("Quit: ", 1);
	else if (s == SIGILL)
		ft_putstr_fd("Illegal instruction: ", 1);
	else if (s == SIGTRAP)
		ft_putstr_fd("Trace/BPT trap: ", 1);
	else if (s == SIGABRT)
		ft_putstr_fd("Abort trap: ", 1);
	else if (s == SIGEMT)
		ft_putstr_fd("EMT trap: ", 1);
	else if (s == SIGFPE)
		ft_putstr_fd("Floating point exception: ", 1);
	else if (s == SIGKILL)
		ft_putstr_fd("Killed: ", 1);
	else if (s == SIGBUS)
		ft_putstr_fd("Bus error: ", 1);
	else if (s == SIGSEGV)
		ft_putstr_fd("Segmentation fault: ", 1);
	else if (s == SIGSYS)
		ft_putstr_fd("Bad system call: ", 1);
}

static void		ft_signumprt(int s)
{
	if (s != SIGINT && s != SIGPIPE)
		ft_putnbr_fd(s, 1);
	if (s != SIGPIPE)
		ft_putendl_fd(NULL, 1);
}

void			ft_sigprint(int s)
{
	if (!WIFSIGNALED(s))
		return ;
	s = WTERMSIG(s);
	g_exitcode = s + 128;
	if (s == SIGHUP || s == SIGINT || s == SIGQUIT || s == SIGILL ||
		s == SIGTRAP || s == SIGABRT || s == SIGEMT || s == SIGFPE ||
		s == SIGKILL || s == SIGBUS || s == SIGSEGV || s == SIGSYS)
		ft_sigprint1(s);
	else if (s == SIGALRM)
		ft_putstr_fd("Alarm clock: ", 1);
	else if (s == SIGTERM)
		ft_putstr_fd("Terminated: ", 1);
	else if (s == SIGXCPU)
		ft_putstr_fd("Cputime limit exceeded: ", 1);
	else if (s == SIGXFSZ)
		ft_putstr_fd("Filesize limit exceeded: ", 1);
	else if (s == SIGVTALRM)
		ft_putstr_fd("Virtual timer expired: ", 1);
	else if (s == SIGPROF)
		ft_putstr_fd("Profiling timer expired: ", 1);
	else if (s == SIGUSR1)
		ft_putstr_fd("User defined signal 1: ", 1);
	else if (s == SIGUSR2)
		ft_putstr_fd("User defined signal 2: ", 1);
	ft_signumprt(s);
}
