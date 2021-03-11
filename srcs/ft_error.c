#include "shell.h"

int		ft_syntaxerrorprint(int ret, char *arg)
{
	if (arg == NULL)
		arg = "newline";
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("syntax error near unexpected token `", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd("\'", 2);
	g_exitcode = 258;
	return (ret);
}

int		ft_issyntaxerror(char *arg)
{
	if (arg == NULL)
		return (1);
	if (ft_strncmp(arg, "<", 2) == 0 ||
		ft_strncmp(arg, ">", 2) == 0 ||
		ft_strncmp(arg, ">>", 3) == 0)
		return (1);
	return (0);
}

void	ft_error(char *cmd, char *arg, char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	if (cmd != NULL)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
	}
	if (arg != NULL)
	{
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": ", 2);
	}
	if (msg != NULL)
		ft_putstr_fd(msg, 2);
	ft_putendl_fd(NULL, 2);
}
