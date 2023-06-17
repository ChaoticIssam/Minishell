#include "minishell.h"

int	ft_isspecial(char c)
{
	return (c == '6' || c == '4' || c == '3');
}

char	*toknz_list(char *str)
{
	int		i;
	int		j;
	char	*array;

	array = NULL;
	i = 0;
	j = 0;
	array = calloc(sizeof(char), ft_strlen(str) + 1); //**
	while (str[i])
	{
		if (str[i] == '>' && str[i + 1] == '>')
		{
			array[j] = '9';
			i++;
		}
		else if (str[i] == '<' && str[i + 1] == '<')
		{
			array[j] = '8';
			i++;
		}
		// else if (str[i] == '$')
		// 	array[j] = '7';
		else if (str[i] == '|')
			array[j] = '6';
		else if (str[i] == '>')
			array[j] = '5';
		else if (str[i] == '<')
			array[j] = '4';
		else if (str[i] == '"' || str[i] == '\'')
			array[j] = '3';
		else if (str[i] == ' ' || str[i] == '\t' || str[i] == '\v')
			array[j] = '2';
		else
			array[j] = '1';
		i++;
		j++;
	}
	array[i] = '\0';
	return (array);
}

// int	count_token(char *list)
// {
// 	int	count;
// 	int	lock;
// 	int	tmp;
// 	int	i;

// 	i = 0;
// 	count = 0;
// 	lock = 1;
// 	tmp = 0;
// 	while (list[i])
// 	{
// 		if (list[i] != tmp)
// 			lock = 1;
// 		if ((ft_isspecial(list[i]) || list[i] == '1') && list[i] != '5' && lock)
// 		{
// 			count++;
// 			lock = 0;
// 			tmp = list[i];
// 		}
// 		i++;
// 	}
// 	return (count);
// }

/**/ int count_ptr(char *list)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (list[i] && list[i] == '2')
		i++;
	while (list[i])
	{
		if (list[i] == '3')
		{
			i = find_quotes_pair(list, i + 1) + 1;
			count++;
		}
		if (list[i] == '1' && (list[i + 1] == '2' || !list[i + 1] || list[i
				+ 1] >= 52))
			count++;
		else if (list[i] >= 52)
			return (count);
		i++;
	}
	return (count);
}

int	count_pipe(char *list)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (list[i])
	{
		if (list[i] == '6')
			count++;
		i++;
	}
	return (count);
}

// /**/char **return_commandes(char *list, char *line)
// {
// 	char	**commande;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	while (list[i] && list[i] == '2')
// 		i++;
// 	while (list[i] && list[i] != '6')
// 	{

// 	}
// }

char	**return_it(char *list, char *str, int bool)
{
	char		**commande;
	static int	i;
	int			x;
	int			start1;
	int			lock;
	int			lock1;
	int			tmp;
	int			start;
	int			end;

	x = 0;
	lock = 0;
	lock1 = 1;
	tmp = 0;
	start = 0;
	start1 = 0;
	end = 0;
	commande = malloc(sizeof(char *) * count_ptr(list) + 1);
	if (bool == 1)
		i = 0;
	if (list[i] == '6')
		i++;
	while (list[i] == '2')
		i++;
	while (list[i] && list[i] != '6')
	{
		if (list[i] == '3')
		{
			commande[x] = quotes_quotes(str, list, i);
			i = sec_q_rex(list, sec_q(list));
			start = i + 1;
			x++;
		}
		if (((list[i] != tmp) || !list[i + 1]))
		{
			end = i - 1;
			if (!list[i + 1])
				end = i;
			start1 = i;
			lock1 = 0;
			lock = 1;
		}
		if ((ft_isspecial(list[i]) || list[i] == '1') && list[i] != '3' && lock
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
		if (!lock1 && list[i] != '3' && str[start] != '"' && str[start] != '\''
			&& end >= start)
		{
			commande[x] = ft_substr(str, start, end - start + 1);
			x++;
		}
		if (list[i] == '2' && list[i + 1] == '2')
		{
			while (list[i] == '2')
				i++;
			i--;
			start = i;
			lock1 = 0;
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
		if (tokenz[i] == '3' || tokenz[i + 1] == 0)
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
		if (tokenz[i] == '3' && tokenz[i + 1] == '1')
		{
			i++;
			ptr[j] = str[i];
		}
		else if (tokenz[i] == '3' || (tokenz[i] == '3' && !tokenz[i + 1]))
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

int	sec_q(char *tknz)
{
	int	i;

	i = ft_strlen(tknz) - 1;
	while (i >= 0)
	{
		if (tknz[i] == '3')
			return (i);
		i--;
	}
	return (0);
}

int	sec_q_rex(char *tknz, int end)
{
	if (tknz[end + 1] == '1')
	{
		while (tknz[end])
		{
			if (tknz[end + 1] == '2')
				return (end);
			end++;
		}
	}
	return (end);
}

int	frst_q(char *tknz)
{
	int	i;

	i = 0;
	while (tknz[i])
	{
		if (tknz[i] == '3')
			return (i);
		i++;
	}
	return (0);
}

int	frst_q_rex(char *tknz, int start)
{
	if (tknz[start - 1] == '1')
	{
		while (start >= 0)
		{
			if (tknz[start - 1] == '2')
				return (start);
			start--;
		}
	}
	return (start);
}

char	*quotes_quotes(char *str, char *tknz, int start)
{
	int		i;
	int		j;
	char	*ptr;
	int		numoq;

	ptr = malloc(sizeof(char) * 100);
	i = frst_q_rex(tknz, frst_q(tknz));
	numoq = num_of_q(tknz, start);
	j = 0;
	while (i < sec_q_rex(tknz, sec_q(tknz)) + 1 && numoq % 2 == 0)
	{
		if (tknz[i] == '3')
			i++;
		if (tknz[i] == '1' || tknz[i] == '2')
		{
			ptr[j] = str[i];
			i++;
			j++;
		}
		if (!tknz[i])
		{
			ptr[j] = '\0';
			return (ptr);
		}
	}
	if (i == sec_q_rex(tknz, sec_q(tknz) + 2) && sec_q_rex(tknz, sec_q(tknz))
		+ 1 > 0)
	{
		ptr[j] = '\0';
		return (ptr);
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
	while (env[i])
	{
		if (!ft_strncmp(s->var, var_gett(env, i)))
		{
			path = get_path(env, i);
			return (path);
		}
		i++;
	}
	return (NULL);
}

int	num_of_q(char *list, int start)
{
	int	count;

	count = 0;
	while (list[start])
	{
		if (list[start] == '3')
			count++;
		start++;
	}
	return (count);
}
