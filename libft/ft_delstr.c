#include "libft.h"

char	**ft_delstr(char **arr, size_t n, size_t count)
{
	size_t	i;
	size_t	j;
	char	**temp;

	i = 0;
	while (arr[i])
		i++;
	i = i + 1 - count;
	if (!(temp = (char**)malloc(i * sizeof(char*))))
		return (0);
	i = 0;
	j = 0;
	while (arr[i])
		if (i != n)
			temp[j++] = arr[i++];
		else
			while (count--)
				free(arr[i++]);
	temp[j] = 0;
	free(arr);
	return (temp);
}
