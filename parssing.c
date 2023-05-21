#include "minishell.h"

int	ft_isspecial(char c)
{
	return (c == '6' || c == '5' || c == '4' || c == '3');
}

char	*toknz_list(char *str)
{
	int		i;
	char	*array;

	array = NULL;
	i = 0;
	array = calloc(sizeof(char), ft_strlen(str) + 1);//**
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
		if ((ft_isspecial(list[i]) || list[i] == '1') && lock)
		{
			count++;
			lock = 0;
			tmp = list[i];
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
	end = 0;
	commande = malloc(sizeof(char *) * count_token(list));
	while (i <= ft_strlen(list))
	{
		if ((list[i] != tmp) || !list[i])
		{
			end = i - 1;
			lock1 = 0;
			lock = 1;
		}
		if ((ft_isspecial(list[i]) || list[i] == '1') && lock)
		{
			start = i;
			lock = 0;
			lock1 = 1;
			tmp = list[i];
		}
		if (!lock1)
		{
			commande[x] = ft_substr(str, start, end - start + 1);
			x++;
		}
		i++;
	}
	return (commande);
}
