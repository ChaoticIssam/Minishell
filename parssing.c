#include "minishell.h"

int	ft_isspecial(char c)
{
	return (c == '6' || c == '4' || c == '3');
}

char	*toknz_list(char *str)
{
	int		i;
	char	*array;

	array = NULL;
	i = 0;
	array = calloc(sizeof(char), ft_strlen(str) + 1); //**
	while (str[i])
	{
		if (str[i] == '|')
			array[i] = '6';
		else if (str[i] == '"')
			array[i] = '5';
		else if (str[i] == '<')
			array[i] = '4';
		else if (str[i] == '>')
			array[i] = '3';
		else if (str[i] == ' ' || str[i] == '\t' || str[i] == '\v')
			array[i] = '2';
		else
			array[i] = '1';
		i++;
	}
	array[i] = '\0';
	return (array);
}

int	count_token(char *list)
{
	int	count;
	int	lock;
	int	tmp;
	int	i;

	i = 0;
	count = 0;
	lock = 1;
	tmp = 0;
	while (list[i])
	{
		if (list[i] != tmp)
			lock = 1;
		if ((ft_isspecial(list[i]) || list[i] == '1') && list[i] != '5' && lock)
		{
			count++;
			lock = 0;
			tmp = list[i];
		}
		else if (list[i] == '5' && find_quotes_pair(list, i + 1))
		{
			i++;
			while (list[i])
			{
				if (list[i] == '5')
				{
					count++;
					break ;
				}
				i++;
			}
		}
		i++;
	}
	return (count);
}

char	**return_it(char *list, char *str)
{
	char	**commande;
	int		i;
	int		x;
	int		start1;
	int		lock;
	int		lock1;
	int		tmp;
	int		start;
	int		end;

	i = 0;
	x = 0;
	lock = 0;
	lock1 = 1;
	tmp = 0;
	start = 0;
	start1 = 0;
	end = 0;
	commande = malloc(sizeof(char *) * count_token(list) + 1);
	while (i < ft_strlen(list))
	{
		if (list[i] == '5')
		{
			commande[x] = in_quotes(list, str, start1);
			printf("[1]commande==<%s>|| x == %d\n\n", commande[x], x);
			i = i + ft_strlen(commande[x]) - 1;
			printf("[1-2]i ==> {-%d-}\n", i);
			start = i;
			x++;
		}
		if (((list[i] != tmp) || !list[i + 1]))
		{
			if (!list[i + 1])
				end = i;
			else
				end = i - 1;
			start1 = i;
			lock1 = 0;
			lock = 1;
		}
		if (list[i] == '1' && list[i + 1] == '5')
		{
			printf("[2]->i == %d\n", i);
			lock1 = 1;
			lock = 0;
		}
		if (list[i] == '1' && list[i + 1] == '6')
		{
			end = i;
			lock = 0;
			lock1 = 0;
			tmp = list[i];
		}
		if ((ft_isspecial(list[i]) || list[i] == '1') && list[i] != '5' && lock
			&& list[i + 1])
		{
			start = i;
			lock = 0;
			lock1 = 1;
			tmp = list[i];
		}
		if (!lock1 && list[i] != '5' && str[start] != '"')
		{
			// printf("[3-1] ---> start == %d || end == %d\n", start, end);
			commande[x] = ft_substr(str, start, end - start + 1);
			printf("[3]commande==<%s>|| x == %d\n\n", commande[x], x);
			x++;
		}
		i++;
	}
	commande[x] = NULL;
	return (commande);
}

int	find_quotes_pair(char *tokenz, int i)
{
	while (tokenz[i])
	{
		if (tokenz[i] == '5')
			return (i);
		i++;
	}
	return (0);
}

char	*in_quotes(char *tokenz, char *str, int i)
{
	char	*ptr;
	int		len;
	int		j;
	j = 0;
	if (!tokenz || !str)
		return (0);
	if (find_quotes_pair(tokenz, i))
	{
		len = find_quotes_pair(tokenz, find_quotes_pair(tokenz, i + 1));
		ptr = malloc(sizeof(char) * len);
	}
	else
		return (0);
	// printf("i == %d || c == %c\n\n", i, tokenz[i]);
	++i;
	while (tokenz[i] != '2' || tokenz[i])
	{
		if (tokenz[i] == '5' && tokenz[i + 1] == '1')
		{
			i++;
			ptr[j] = str[i];
		}
		else if (tokenz[i] == '5' || (tokenz[i] == '5' && !tokenz[i + 1]))
		{
			ptr[j] = '\0';
			break ;
		}
		ptr[j] = str[i];
		j++;
		i++;
	}
	return (ptr);
}
