int	ft_wordcount(char **arr)
{
	int	c;

	c = 0;
	if (arr == 0)
		return (0);
	while (arr[c] != 0)
		c++;
	return (c);
}
