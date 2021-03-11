#include "libft.h"

static void		ft_memcleanup(char **words, size_t lastw)
{
	while (lastw > 0)
	{
		lastw--;
		if (words[lastw] != NULL)
			free(words[lastw]);
	}
	if (words != NULL)
		free(words);
}

static size_t	ft_putword(const char *str, char c, char **words, size_t wnum)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (str[len] != c && str[len] != '\0')
		len++;
	if (!(words[wnum] = (char *)malloc(sizeof(char) * len + 1)))
	{
		ft_memcleanup(words, wnum);
		return (0);
	}
	while (i < len)
	{
		words[wnum][i] = *str;
		i++;
		str++;
	}
	words[wnum][i] = '\0';
	return (len);
}

static size_t	ft_countwords(const char *str, char c)
{
	size_t	i;
	size_t	wcount;

	i = 0;
	wcount = 0;
	while (str[i] == c && str[i] != '\0')
		i++;
	while (str[i] != '\0')
	{
		while (str[i] != '\0' && str[i] != c)
			i++;
		while (str[i] == c && str[i] != '\0')
			i++;
		wcount++;
	}
	return (wcount);
}

char			**ft_split(char const *s, char c)
{
	size_t	wnum;
	size_t	wcount;
	size_t	wlen;
	char	**words;

	if (s == NULL)
		return (NULL);
	wcount = ft_countwords(s, c);
	if (!(words = (char **)malloc(sizeof(char *) * (wcount + 1))))
		return (NULL);
	wnum = 0;
	while (wnum < wcount && *s != '\0')
	{
		while (*s == c && *s != '\0')
			s++;
		if (*s != '\0')
			wlen = ft_putword(s, c, words, wnum);
		if (wlen == 0)
			return (NULL);
		wnum++;
		s += wlen;
	}
	words[wnum] = NULL;
	return (words);
}
