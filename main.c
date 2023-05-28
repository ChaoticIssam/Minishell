#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>

int	main(void)
{
	char	*line;
	char	*tmp;
	// int		i;

	// char *arc = NULL;
	// t_commandes	*comm;
	// char *commande = NULL;
	// i = 0;
	// int	*arr;
	// while (1)
	// {
		line = readline("Minishell$ ");
		if (line == NULL || !ft_strncmp(line, "exit"))
			exit(0);
		tmp = toknz_list(line);
		// while (i < count_token(tmp))
		// {
			return_it(tmp, line);
			// ft_putstr(return_it(tmp, line)[i]);
			printf("\n");
			// i++;
		// }
		// i = 0;
	// }
}
void	print_stuff(int *start)
{
	int	i;

	i = 0;
	while (start[i])
	{
		printf("%d", start[i]);
		i++;
	}
}
