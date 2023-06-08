#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>

int	main(void)
{
	char	*line;
	char	*tmp;
	char	**commande = NULL;
	t_commandes	*m;
	int		i;
	i = 0;
	m = malloc(sizeof(t_commandes));
	while (1)
	{
		line = readline("Minishell$ ");
		if (line == NULL || !ft_strncmp(line, "exit"))
			exit(0);
		tmp = toknz_list(line);
		commande = return_it(tmp,line);
		m->s = commande;
		// printf("last == %d, first == %d\n", sec_q(tmp), frst_q(tmp));
		// while (i < ft_strlen(tmp))
		// {
		// 	if (tmp[i] == '5')
		// 	{
		// 		printf("*******>%s\n", quotes_quotes(line, tmp, i));
		// 		i = find_quotes_pair(tmp, i);
		// 	}
		// // 	ft_putstr(m->s[i]);
		// // 	// ft_putstr(m->s[i]);
		// 	i++;
		// }
		// i = 0;
		while (i < count_token(tmp))
		{
			// return_it(tmp, line);
			ft_putstr(m->s[i]);
			printf("\n");
			i++;
		}
		i = 0;
	}
}
