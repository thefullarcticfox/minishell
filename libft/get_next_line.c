#include "get_next_line.h"

static void	ft_cleanlastbuf(char **lastbuf)
{
	if (lastbuf == NULL)
		return ;
	free(*lastbuf);
	*lastbuf = NULL;
}

static int	ft_processnl(char **line, char *buf, char **lastbuf)
{
	char	*nl;
	char	*temp;

	if (buf == NULL)
		buf = *lastbuf;
	if ((nl = ft_strchr(buf, '\n')))
	{
		*nl = '\0';
		temp = *line;
		if (!(*line = ft_strjoin(*line, buf)))
			return (-1);
		free(temp);
		temp = *lastbuf;
		if (!(*lastbuf = ft_strdup(nl + 1)))
			return (-1);
		free(temp);
		return (1);
	}
	temp = *line;
	if (!(*line = ft_strjoin(*line, buf)))
		return (-1);
	free(temp);
	ft_cleanlastbuf(lastbuf);
	return (0);
}

static int	ft_readlines(char **line, int fd, char **lastbuf)
{
	char		buf[BUFFER_SIZE + 1];
	ssize_t		rdres;
	int			nlres;

	rdres = -1;
	while ((rdres = read(fd, buf, BUFFER_SIZE)) >= 0)
	{
		if (*line == NULL)
			if (!(*line = ft_strdup("")))
				return (-1);
		buf[rdres] = '\0';
		if (rdres == 0)
			return (0);
		nlres = ft_processnl(line, buf, lastbuf);
		if (nlres != 0)
			return (nlres);
	}
	return (rdres);
}

int			get_next_line(int fd, char **line)
{
	static char		*lastbuf[FD_LIMIT];
	int				bufcheckres;
	int				rdres;

	if (fd < 0 || fd >= FD_LIMIT || BUFFER_SIZE <= 0 || line == NULL)
		return (-1);
	*line = NULL;
	if (lastbuf[fd] != NULL)
	{
		if (!(*line = ft_strdup("")))
			return (-1);
		bufcheckres = ft_processnl(line, NULL, &lastbuf[fd]);
		if (bufcheckres != 0)
			return (bufcheckres);
	}
	rdres = ft_readlines(&(*line), fd, &lastbuf[fd]);
	if (rdres <= 0)
		ft_cleanlastbuf(&lastbuf[fd]);
	return (rdres);
}
