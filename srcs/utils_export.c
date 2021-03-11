#include "shell.h"

int			u_isvalid(char *line)
{
	if (*line >= 0 && *line < 'A')
		return (0);
	if ((*line > 'Z' && *line < '_') || *line > 'z')
		return (0);
	while (*line != '=' && *line && *line != ' ')
	{
		if ((*line < 'A' || *line > 'Z') && (*line < 'a' || *line > 'z') &&
			(*line < '0' || *line > '9') && *line != '_')
			return (0);
		line++;
	}
	return (1);
}

int			u_find_var(char *line, t_env *env)
{
	size_t	i;
	size_t	j;

	i = -1;
	while (++i < env->n)
	{
		j = 0;
		while (env->envp[i][j] && line[j] && line[j] != '=' &&
				env->envp[i][j] != '=' && env->envp[i][j] == line[j])
			j++;
		if (env->envp[i][j] == '=' && line[j] == '=')
			return (i);
	}
	return (-1);
}

static void	my_sort_envp(char **s)
{
	int		i;
	int		flag;
	char	*swap;

	i = 1;
	flag = 0;
	while (1)
	{
		if (s[i] == 0 && flag == 1)
		{
			i = 1;
			flag = 0;
		}
		else if (s[i] == 0 && flag == 0)
			break ;
		else if (ft_strcmp(s[i - 1], s[i]) > 0)
		{
			flag = 1;
			swap = s[i];
			s[i] = s[i - 1];
			s[i - 1] = swap;
		}
		else
			i++;
	}
}

void		u_sort_and_print(t_env *env)
{
	char	**sorted;
	int		i;
	int		j;

	if (!(sorted = (char**)malloc((env->n + 1) * sizeof(char*))))
		exit_status(NULL);
	ft_memcpy(sorted, env->envp, (env->n + 1) * sizeof(char*));
	if (sorted[0] && sorted[1])
		my_sort_envp(sorted);
	i = -1;
	while (sorted[++i])
	{
		ft_putstr_fd("declare -x ", 1);
		j = -1;
		while (sorted[i][++j] != '=')
			ft_putchar_fd(sorted[i][j], 1);
		write(1, "=", 1);
		write(1, "\"", 1);
		while (sorted[i][++j])
			ft_putchar_fd(sorted[i][j], 1);
		write(1, "\"", 1);
		write(1, "\n", 1);
	}
	free(sorted);
}
