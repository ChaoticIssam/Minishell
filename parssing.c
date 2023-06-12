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
		if (str[i] == '$')
			array[i] = '7';
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
			commande[x] = quotes_quotes(str, list, i);
			i = find_quotes_pair(list, i);
			start = i + 1;
			x++;
		}
		if (((list[i] != tmp) || !list[i + 1]))
		{
			end = i;
			start1 = i;
			lock1 = 0;
			lock = 1;
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
		if (list[i] == '1' && list[i - 1] == '2' && !list[i + 1])
		{
			commande[x] = &str[i];
			x++;
		}
		if (!lock1 && list[i] != '5' && str[start] != '"' && end >= start)
		{
			commande[x] = ft_substr(str, start, end - start + 1);
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
		if (tokenz[i] == '2' || tokenz[i + 1] == 0)
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

int	sec_q(char *tknz, int start)
{
	while (tknz[start] != '5')
		start++;
	start++;
	while (tknz[start])
	{
		if (tknz[start] == '5')
		{
			if (tknz[start + 1] == '1')
			{
				start++;
				while (tknz[start] == '1')
					start++;
			}
			return (start);
		}
		start++;
	}
	return (0);
}

int	frst_q(char *tknz, int start)
{
	int	i;

	i = sec_q(tknz, start);
	while (i >= 0)
	{
		if (tknz[i] == '2' && i < sec_q(tknz, start))
			return (i);
		i--;
	}
	return (0);
}

char	*quotes_quotes(char *str, char *tknz, int start)
{
	int		i;
	int		j;
	char	*ptr;

	ptr = malloc(sizeof(char) * sec_q(tknz, start));
	i = frst_q(tknz, start);
	j = 0;
	i++;
	while (i <= sec_q(tknz, start))
	{
		if (tknz[i] == '5')
			i++;
		if (tknz[i] == '2' || tknz[i] == '\0')
		{
			ptr[j] = '\0';
			return (ptr);
		}
		else if (tknz[i] == '1')
			ptr[j] = str[i];
		j++;
		i++;
	}
	return (0);
}

int	env_len(t_commandes *m)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	j = 0;
	count = 0;
	while (m->s[i])
	{
		if (m->s[i][j] == '$')
		{
			j++;
			while (m->s[i][j] && m->s[i][j] != ' ')
			{
				count++;
				j++;
			}
			if (m->s[i][j] == ' ' || !m->s[i][j])
				return (count);
		}
		i++;
	}
	return (0);
}

char	*fill_var(t_env *s, t_commandes *m, int i, int j)
{
	char	*var;
	int		x;

	var = malloc(sizeof(char) * s->env_len + 1);
	x = 0;
	j++;
	while (m->s[i][j] && m->s[i][j] != ' ')
	{
		var[x] = m->s[i][j];
		j++;
		x++;
	}
	var[x] = '\0';
	return (var);
}

char	*var_gett(char **env, int i)
{
	int		j;
	char	*envv;

	envv = malloc(sizeof(char) * 100);
	j = 0;
	while (env[i][j])
	{
		if (env[i][j] == '=')
			return (envv);
		envv[j] = env[i][j];
		j++;
	}
	return (0);
}

char	*get_path(char **env, int i)
{
	int		j;
	int		x;
	char	*envr;

	envr = malloc(sizeof(char) * 100);
	j = 0;
	x = 0;
	while (env[i][j])
	{
		if (env[i][j] == '=')
		{
			j++;
			while (env[i][j])
			{
				envr[x] = env[i][j];
				x++;
				j++;
			}
			if (!env[i][j])
				return (envr);
		}
		j++;
	}
	return (0);
}

char	*fill_path(char **env, t_env *s)
{
	int		i;
	int		j;
	char	*path;

	i = 0;
	j = 0;
	path = malloc(sizeof(char) * 100);
	while (env[i][j] && env[i][j] != '=')
		j++;
	j++;
	while (i < 36)
	{
		if (!ft_strncmp(s->var, var_gett(env, i)))
		{
			path = get_path(env, i);
			return (path);
		}
		i++;
	}
	return (0);
}
