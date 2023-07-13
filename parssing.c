/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deimos <deimos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 15:58:57 by iszitoun          #+#    #+#             */
/*   Updated: 2023/07/12 22:24:26 by deimos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isredi(char c)
{
	if (c == '9' || c == '8' || c == '4' || c == '5')
		return(1);
	return(0);
}

int	ft_isspecial(char c)
{
	return (c == '6' || c == '4' || c == '3');
}

int	expand_erreur(char *list)
{
	int	i;

	i = 0;
	while (list[i])
	{
		if (ft_isredi(list[i]) == 1 && ft_isredi(list[i + 1]) == 1)
			lerreurat(9);
		i++;
	}
	return (1);
}

int	quote_bfr_pipe(char *str, int i, char q)
{
	int	count;
	
	count = 0;
	while (str[i] != '|' && str[i])
	{
		if (str[i] == q)
			count++;
		if (count % 2 == 0 && (str[i + 1] == '|' || !str[i + 1]))
		{
			while(str[i] && i > 0 && (str[i] == ' ' || str[i] == '\t'))
				i--;
			return (i);
		}
		i++;
	}
	return (0);
}

char	*toknz_list(char *str)
{
	int		i;
	int		j;
	int		tmp;
	int		count;
	char	*array;

	array = NULL;
	i = 0;
	j = 0;
	tmp = 0;
	count = 0;
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
		else if (str[i] == '|')
			array[j] = '6';
		else if (str[i] == '>')
			array[j] = '5';
		else if (str[i] == '<')
			array[j] = '4';
		else if (str[i] == '"')
		{
			array[j] = '3';
			if (quote_bfr_pipe(str, i, '"'))
			{
				tmp = quote_bfr_pipe(str, i, '"');
				i++;
				j++;
				while (i < tmp)
				{
					array[j] = '1';
					if(str[i] == '"' || str[i] == '\'')
						array[j] = '3';
					i++;
					j++;
				}
				if (str[i] == '"')
					array[j] = '3';
				else
					array[j] = '1';
			}	
			else if (!quote_bfr_pipe(str, i, '"'))
			{
				i++;
				j++;
				count++;
				while (i < find_quotes_pair(str, '"'))
				{
					if (str[i] == '"')
					{
						array[j] = '3';
						count++;
						j++;
						i++;
					}
					else if (str[i] == '|' && count % 2 == 0)
					{
						array[j] = '6';
						i++;
						j++;
					}
					else
					{
						array[j] = '1';
						j++;
						i++;
					}
				}
				if (str[i] == '"')
					array[j] = '3';
				else
					lerreurat(3);
			}
		}
		else if (str[i] == '\'')
		{
			array[j] = '0';
			if (quote_bfr_pipe(str, i, '\''))
			{
				tmp = quote_bfr_pipe(str, i, '\'');
				i++;
				j++;
				while (i < tmp)
				{
					array[j] = '1';
					if(str[i] == '\'')
						array[j] = '0';
					i++;
					j++;
				}
				if (str[i] == '\'')
					array[j] = '0';
				else
					array[j] = '1';
			}
			else if (!quote_bfr_pipe(str, i, '\''))
			{
				while (i < find_quotes_pair(str, '\''))
				{
					if (str[i] == '\'')
					{
						array[j] = '0';
						j++;
						i++;
					}
					else
					{
						array[j] = '1';
						j++;
						i++;
					}
				}
				if (str[i] == '\'')
					array[j] = '0';
				else
					lerreurat(0);
			}
		}
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

/*count_strings_in_commandes*/ int count_ptr(char *list, int bool)
{
	int	count;
	static int	i;
	static int	j;
	int			len;

	if (bool == 1)
		i = 0;
	if (bool == 0)
		i = j;
	count = 0;
	len = ft_strlen(list);
	while (list[i] && list[i] == '2')
		i++;
	while (i >= 0 && i + 1 <= len && list[i])
	{
		if (list[i] == '3')
		{
			i = sec_q_rex(list, sec_q(list)) + 1;
			count++;
		}
		if (list[i] == '0')
		{
			i = sec_q_rex(list, sec_s_q(list)) + 1;
			count++;
		}
		if (list[i] == '1' && (list[i + 1] == '2' || !list[i + 1])
			&& list[i] != '6')
			count++;
		if (list[i] == '1' && list[i + 1] >= 52)
			count++;
		else if (list[i] >= 52)
		{
			i++;
			if (bool == 1)
				j = i;
			return (count);
		}
		i++;
	}
	return (count);
}

/*count_redirections*/ int count_redi(char *list)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (list[i] && list[i] == '2')
		i++;
	while (list[i])
	{
		if (list[i] >= 52 && list[i] != '6')
			count++;
		else if (list[i] == '6')
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
	check_pipe(list);
	while (list[i])
	{
		if (list[i] == '6')
			count++;
		i++;
	}
	return (count);
}

int	check_pipe(char *list)
{
	int	i;
	
	i = ft_strlen(list) -1;
	if (i >= 0)
	{
		if (list[i] == '6')
			lerreurat(6);
		while (list[i] == '2')
			i--;
		if (list[i] == '6')
			lerreurat(6);
	}
	return (1);
}

char	**return_commande(char *list, char *str, int bool)
{
	char		**commande;
	static int	i;
	int			j;
	int			x;
	int			lock;
	int			lock1;
	int			tmp;
	int			start;
	int			end;
	int			ptr_num;

	x = 0;
	lock = 0;
	lock1 = 1;
	tmp = 0;
	start = 0;
	j = 0;
	end = 0;
	if (bool == 1)
		i = 0;
	ptr_num = count_ptr(list, bool);
	printf("---->%d\n", ptr_num);
	printf("i ->%d\n", i);
	commande = calloc(sizeof(char *), ptr_num + 2);
	expand_erreur(list);
	if (list[i] == '6' ||)
		i++;
	while (list[i] == '2')
		i++;
	while (i + 1 <= ft_strlen(list) && list[i] && list[i] < 52)
	{
		if (list[i] == '3' || list[i] == '0')
		{
			j = i;
			commande[x] = quotes_quotes(str, list, i);
			if (quote_bfr_pipe(str, i, list[i]))
				i = quote_bfr_pipe(str, i, list[i]);
			else if (!quote_bfr_pipe(str, i, list[i]))
				i = j;
			if (list[i] == '3')
				i = sec_q_rex(list, i);
			else if (list[i] == '0')
				i = sec_q_rex(list, i);
			start = i + 1;
			x++;
		}
		if (((list[i] != tmp) || list[i + 1] == '6' || !list[i + 1]))
		{
			end = i - 1;
			if (i + 1 <= ft_strlen(list) && !list[i + 1])
				end = i;
			lock1 = 0;
			lock = 1;
			if (i + 1 <= ft_strlen(list) && list[i + 1] == '6')
			{
				end = i;
				if (list[i] == '2')
					end = i - 1;
				lock = 0;
			}
		}
		if ((list[i] == '1') && list[i] != '3' && lock && list[i + 1])
		{
			start = i;
			lock = 0;
			lock1 = 1;
			tmp = list[i];
		}
		if (i != 0 && i + 1 < ft_strlen(list) && list[i] == '1' && list[i
			- 1] == '2' && !list[i + 1])
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
	return (commande);
}

char	**return_file(char *list, char *str, int bool)
{
	char		**files;
	static int	i;
	int			x;
	int			start;
	int			end;

	files = malloc(sizeof(char *) * 100);
	x = 0;
	start = 0;
	end = 0;
	if (bool == 1)
		i = 0;
	if (list[i] == '6')
		i++;
	while (list[i] == '2')
		i++;
	while (list[i] && list[i] != '6')
	{
		if (ft_isredi(list[i]) == 1)
		{
			start = i;
			if (i > 0)
				start = i + 1;
			while (list[i] != '2' && list[i])
				i++;
			if (i > start)
				end = i;
			printf("end ->%d and start ->%d\n", end, start);
			files[x] = ft_substr(str, start, end - start + 1);
			x++;
		}
		i++;
	}
	return (files);
}

int	find_quotes_pair(char *str , char c)
{
	int	i = ft_strlen(str);
	while (i >= 0)
	{
		if (str[i] == c)
			return (i);
		i--;
	}
	return (0);
}

// char	*in_quotes(char *tokenz, char *str, int i)
// {
// 	char	*ptr;
// 	int		len;
// 	int		j;

// 	j = 0;
// 	if (!tokenz || !str)
// 		return (0);
// 	if (find_quotes_pair(tokenz, i))
// 	{
// 		len = find_quotes_pair(tokenz, find_quotes_pair(tokenz, i + 1));
// 		ptr = malloc(sizeof(char) * len);
// 	}
// 	else
// 		return (0);
// 	++i;
// 	while (tokenz[i] != '2' || tokenz[i])
// 	{
// 		if (tokenz[i] == '3' && tokenz[i + 1] == '1')
// 		{
// 			i++;
// 			ptr[j] = str[i];
// 		}
// 		else if (tokenz[i] == '3' || (tokenz[i] == '3' && !tokenz[i + 1]))
// 		{
// 			ptr[j] = '\0';
// 			break ;
// 		}
// 		ptr[j] = str[i];
// 		j++;
// 		i++;
// 	}
// 	return (ptr);
// }

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
	return(lerreurat(0));
}

int	sec_s_q(char *tknz)
{
	int	i;

	i = ft_strlen(tknz) - 1;
	while (i >= 0)
	{
		if (tknz[i] == '0')
			return (i);
		i--;
	}
	return(lerreurat(0));
}

int	sec_q_rex(char *tknz, int end)
{
	if (tknz[end + 1] == '1')
	{
		while (tknz[end])
		{
			if (tknz[end + 1] == '2' || tknz[end + 1] == '6')
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

int	frst_s_q(char *tknz)
{
	int i;

	i = 0;
	while (tknz[i])
	{
		if (tknz[i] == '0')
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
			if (tknz[start - 1] == '2' || start == 0)
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
	int		last;
	char	*ptr;
	int		numoq;
	
	i = 0;
	last = 0;
	numoq = 0;
	ptr = malloc(sizeof(char) * 100);
	if (tknz[start] == '3')
	{
		i = frst_q_rex(tknz, start);
		last = sec_q_rex(tknz, sec_q(tknz)) + 1;
		numoq = num_of_q(tknz, start);
	}
	else if (tknz[start] == '0')
	{
		i = frst_q_rex(tknz, start);
		last = sec_q_rex(tknz, sec_s_q(tknz)) + 1;
		numoq = num_of_s_q(tknz, start);
	}
	j = 0;
	while (i < last && numoq % 2 == 0)
	{
		if (tknz[i] == '0' || tknz[i] == '3')
			i++;
		if (tknz[i] == '1')
		{
			ptr[j] = str[i];
			i++;
			j++;
		}
		if (!tknz[i] || tknz[i] == '2' || tknz[i] == '6')
		{
			ptr[j] = '\0';
			return (ptr);
		}
	}
	if ((tknz[i] == '6' && i > sec_q_rex(tknz, sec_q(tknz))))
	{
		ptr[j] = '\0';
		return (ptr);
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
	while (m->commande[i] && m->commande[i][j])
	{
		if (m->commande[i][j] == '$')
		{
			j++;
			while (m->commande[i][j] && m->commande[i][j] != ' ')
			{
				count++;
				j++;
			}
			if (m->commande[i][j] == ' ' || !m->commande[i][j])
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
	while (m->commande[i][j] && m->commande[i][j] != ' ')
	{
		var[x] = m->commande[i][j];
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

int	num_of_s_q(char *list, int start)
{
	int	count;

	count = 0;
	while (list[start])
	{
		if (list[start] == '0')
			count++;
		start++;
	}
	return (count);
}

int	lerreurat(int error)
{
	if (error == 3)
	{
		printf("ERROR QUOTES!\n");
		exit(0);
	}
	if (error == 6)
	{
		printf("ERROR PIPE!\n");
		exit(0);
	}
	if (error == 9)
	{
		printf("ERROR REDIRECTION!\n");
		exit(0);
	}
	return (0);
}
