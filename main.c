/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deimos <deimos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 15:58:37 by iszitoun          #+#    #+#             */
/*   Updated: 2023/07/12 17:37:11 by deimos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>

void	check_bill(t_commandes *tmp, t_env *senv, char **env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (tmp->commande[i])
	{
		if (tmp->commande[i][j] == '$')
		{
			senv->var = fill_var(senv, tmp, i, j);
			senv->path = fill_path(env, senv);
			if (senv->path != NULL)
			{
				free(tmp->commande[i]);
				tmp->commande[i] = senv->path;
			}
			else
				return ;
		}
		i++;
	}
}

int	main(int ac, char **av, char **env)
{
	char		*line;
	char		*list;
	t_commandes	*m;
	t_commandes	*tmp;
	t_env		*senv;
	int			i;
	int			j;
	int			x;

	(void)ac;
	(void)**av;
	i = 0;
	j = 0;
	x = 0;
	senv = malloc(sizeof(t_env));
	tmp = NULL;
	while (1)
	{
		(void)env;
		printf("\033[0;31m");
		line = readline("Minishell$ ");
		printf("\033[0m");
		add_history(line);
		m = malloc(sizeof(t_commandes));
		tmp = m;
		if (line == NULL || !ft_strncmp(line, "exit"))
			exit(0);
		list = toknz_list(line);
		printf("%s\n", list);
		m->commande = return_commande(list, line, 1);
		m->files = return_file(list, line, 1);
		m->next = NULL;
		senv->env_len = env_len(m);
		check_bill(tmp, senv, env);
		/*print ptrs*/
		while (x < count_redi(list))
		{
			ft_putstr(tmp->files[x]);
			printf("\n");
			x++;
		}
		while (j < count_ptr(list, 1))
		{
			ft_putstr(tmp->commande[j]);
			printf("\n");
			j++;
		}
		/*done printing*/
		while (i < count_pipe(list))
		{
			j = 0;
			x = 0;
			ft_lstadd_back(&tmp, ft_lstnew(line));
			tmp = tmp->next;
			tmp->commande = return_commande(list, line, 0);
			tmp->files = return_file(list, line, 0);
			check_bill(tmp, senv, env);
			/*print ptrs*/
			while (x < count_redi(list))
			{
				ft_putstr(tmp->files[x]);
				printf("\n");
				x++;
			}
			while (tmp->commande[j])
			{
				ft_putstr(tmp->commande[j]);
				printf("<----\n");
				j++;
			}
			/*done printing*/
			i++;
		}
		i = 0;
		j = 0;
		x = 0;
	}
}
