#include "minishell.h"

static int	count_words(char *str, char c)
{
	int	i;
	int	count;

	count = 0;
	i = -1;
	while (str[++i])
		if (str[i] != c && (str[i + 1] == c || !str[i + 1]))
			count++;
	return (count);
}

static void	free_all(char **str)
{
	while (*str)
		free(*str++);
	free(str);
}

char    *ft_substr(char *s, int start, int len)
{
    char    *c;
    int  i;
    int  y;

    i = 0;
    y = ft_strlen(s);
    if (len > y - start)
        len = y - start;
    c = malloc (sizeof(char) * (len + 1));
    if (!c)
        return (0);
    if (start > y)
    {
        c[i] = '\0';
        return (c);
    }
    while (s[start] && i < len)
    {
        c[i] = s[start];
        start++;
        i++;
    }
    c[i] = '\0';
    return (c);
}

char	**ft_split(char *s, char c)
{
	char	**p;
	int		i;
	int		j;
	int		l;

	i = 0;
	l = -1;
	if (!s)
		return (NULL);
	p = malloc(sizeof (char *) * (count_words((char *)s, c) + 1));
	if (!p)
		return (NULL);
	while (++l < count_words((char *)s, c))
	{	
		while (s[i] && s[i] == c)
			i++;
		j = i;
		while (s[i] != c && s[i])
			i++;
		p[l] = ft_substr(s, j, i - j);
		if (!p[l])
			return (free_all(p), NULL);
	}
	return (p[l] = NULL, p);
}
