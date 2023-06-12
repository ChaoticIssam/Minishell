#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>

int	main(int ac, char **av, char **env)
{
	char		*line;
	char		*tmp;
	char		**commande;
	t_commandes	*m;
	t_env		*senv;
	int			i;
	int			j;

	(void)ac;
	(void)**av;
	commande = NULL;
	i = 0;
	j = 0;
	m = malloc(sizeof(t_commandes));
	senv = malloc(sizeof(t_env));
	while (1)
	{
		line = readline("Minishell$ ");
		if (line == NULL || !ft_strncmp(line, "exit"))
			exit(0);
		tmp = toknz_list(line);
		commande = return_it(tmp, line);
		m->s = commande;
		senv->env_len = env_len(m);
		while (i < count_token(tmp))
		{
			// return_it(tmp, line);
			(void)env[i];
			// ft_putstr(m->s[i]);
			// printf("\n");
			if (m->s[i][j] == '$')
			{
				senv->var = fill_var(senv, m, i, j);
				senv->path = fill_path(env, senv);
				printf("%s\n", fill_path(env, senv));
			}
			i++;
		}
		i = 0;
	}
}
