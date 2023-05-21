#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>

int	main(void)
{
	char	*line;
	char	*tmp;
	int		i;

	// char *arc = NULL;
	// t_commandes	*comm = NULL;
	// char *commande = NULL;
	i = 0;
	// int	*arr;
	line = readline("Minishell$ ");
	if (line == NULL || !ft_strncmp(line, "exit"))
		exit(0);
	/*create linked list filled with tokens that represent chars from the readline*/
	tmp = toknz_list(line);
	ft_putstr(tmp);
	printf("\n");
	// char **stx
	//  = ft_split(*return_it(tmp, line), ' ');
	// printf("%s\n\n\n", *return_it(tmp, line));
	while (i < count_token(tmp))
	{
		// printf("i == %d ---> count == %d\n", i, count_token(tmp));
		ft_putstr(return_it(tmp, line)[i]);
		printf("\n");
		i++;
	}
	// printf("\n");
	// printf("count == %d", count_token(tmp));
	// arr = return_string(tmp, line);
	// while (arr[i])
	// {
	// 	printf("%d; ", arr[i]);
	// 	i++;
	// }
	/*push tokenz into a linked list as it should be*/
	// fill_list(tmp, line);
	// print_stuff2(fill_list(tmp, line));
}
/*used for printing linked list elements*/
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

// void	print_stuff2(t_commandes *start)
// {
// 	int	i = 0;
// 	while (start != NULL)
// 	{
// 		while (start->s[i])
// 			printf("%c", start->s[i++]);
// 		start = start->next;
// 	}
// }