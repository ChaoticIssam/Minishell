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
	while (tmp->s[i])
	{
		if (tmp->s[i][j] == '$')
		{
			senv->var = fill_var(senv, tmp, i, j);
			senv->path = fill_path(env, senv);
			if (senv->path != NULL)
			{
				free(tmp->s[i]);
				tmp->s[i] = senv->path;
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
	char		**commande;
	t_commandes	*m;
	t_commandes	*tmp;
	t_env		*senv;
	int			i;
	int			j;

	(void)ac;
	(void)**av;
	commande = NULL;
	i = 0;
	j = 0;
	senv = malloc(sizeof(t_env));
	while (1)
	{
		(void)env;
		line = readline("Minishell$ ");
		m = malloc(sizeof(t_commandes));
		tmp = m;
		if (line == NULL || !ft_strncmp(line, "exit"))
			exit(0);
		list = toknz_list(line);
		m->s = return_it(list, line, 1);
		senv->env_len = env_len(m);
		check_bill(tmp, senv, env);
		/*print ptrs*/while (j < count_ptr(list))
		{
			ft_putstr(tmp->s[j]);
			printf("\n");
			j++;
		}/*done printing*/
		while (i < count_pipe(list))
		{
			j = 0;
			ft_lstadd_back(&tmp, ft_lstnew(NULL));
			tmp = tmp->next;
			tmp->s = return_it(list, line, 0);
			check_bill(tmp, senv, env);
			/*print ptrs*/while (j < count_ptr(list))
			{
				ft_putstr(tmp->s[j]);
				printf("\n");
				j++;
			}/*done printing*/
			i++;
		}
		i = 0;
		j = 0;
	}
}
