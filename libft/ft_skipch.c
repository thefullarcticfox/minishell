char	*ft_skipch(char *line, char c, int flag)
{
	if (flag == 0)
		while (*line == c && *line > 0)
			line++;
	else if (flag == 1)
		while (*line <= c && *line > 0)
			line++;
	else if (flag == 2)
		while (*line >= c && *line > 0)
			line++;
	return (line);
}
