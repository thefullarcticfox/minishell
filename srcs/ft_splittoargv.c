#include "shell.h"

void			ft_freeargv(t_env *env)
{
	size_t	i;

	env->argc = 0;
	if (env->argv == NULL)
		return ;
	i = 0;
	while (env->argv[i] != NULL)
		free(env->argv[i++]);
	free(env->argv);
	env->argv = NULL;
}

static void		ft_braketskip(char *cmd, size_t *i)
{
	char	braket;

	braket = cmd[*i];
	(*i)++;
	while (cmd[*i] && cmd[*i] != braket)
	{
		if (cmd[*i] == '\\' && cmd[(*i) + 1] == '\\')
			(*i) += 2;
		else if (cmd[*i] == '\\' && cmd[(*i) + 1] == '\"')
			(*i) += 2;
		else
			(*i)++;
	}
	if (cmd[*i] == braket)
		(*i)++;
}

static int		ft_doublecheck(char *cmd, char c)
{
	if (c != ';' && c != '|')
		return (1);
	cmd++;
	while (*cmd && *cmd != c)
	{
		if (!ft_isspace(*cmd) && *cmd != c)
			return (1);
		cmd++;
	}
	if (c == ';' && *cmd == '\0')
		return (1);
	if (c == ';' && *cmd == ';')
		ft_error(NULL, NULL, "syntax error near unexpected token `;'");
	if (c == '|' && (*cmd == '\0' || *cmd == '|'))
		ft_error(NULL, NULL, "syntax error near unexpected token `|'");
	g_exitcode = 258;
	return (0);
}

char			**ft_splittoargv(char *cmd, char c)
{
	size_t	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == c && !ft_doublecheck(&cmd[i], c))
			return (NULL);
		if (cmd[i] == c || (c == ' ' && ft_isspace(cmd[i])))
			cmd[i++] = '\n';
		else if (cmd[i] == '\"')
			ft_braketskip(cmd, &i);
		else if (cmd[i] == '\'')
			ft_braketskip(cmd, &i);
		else if ((cmd[i] == '\\' && cmd[i + 1] == '\\') ||
			(cmd[i] == '\\' && cmd[i + 1] == '\"') ||
			(cmd[i] == '\\' && cmd[i + 1] == '\'') ||
			(cmd[i] == '\\' && cmd[i + 1] == '|') ||
			(cmd[i] == '\\' && cmd[i + 1] == ';') ||
			(cmd[i] == '\\' && cmd[i + 1] == ' '))
			i += 2;
		else
			i++;
	}
	return (ft_split(cmd, '\n'));
}
