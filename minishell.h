#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_node
{
	int					token;
	struct s_node		*next;
}						t_node;

typedef struct s_commandes
{
	char				**s;
	struct s_commandes	*next;
}						t_commandes;

typedef struct s_env
{
	char				*var;
	char				*path;
	int					env_len;
	struct s_env		*next;
}						t_env;

int						ft_strncmp(char *s1, char *s2);
int						ft_strlen(char *str);
t_node					*create_node(int arg);
// t_node				*create_ll(char *str);
char					*toknz_list(char *str);
char					**return_it(char *list, char *str);
char					*ft_substr(char *s, int start, int len);
char					**ft_split(char *str, char c);
int						ft_isspecial(char c);
int						get_index(int *list);
char					*in_quotes(char *tokenz, char *str, int i);
int						find_quotes_pair(char *tokenz, int i);
int						*return_string(t_node *list, char *str);
char					*ft_strjoin(char *s1, char *s2);
void					ft_putstr(char *str);
int						count_token(char *list);
void					fill_strct(char **commande);
int						sec_q(char *tknz, int start);
int						frst_q(char *tknz, int start);
char					*quotes_quotes(char *str, char *tknz, int start);
int						env_len(t_commandes *m);
char					*fill_var(t_env *s, t_commandes *m, int i, int j);
char					*get_path(char **env, int i);
char					*fill_path(char **env, t_env *s);
char					*var_gett(char **env, int i);
/* tmp */ void print_stuff(int *start);
/*tmp*/ void print_stuff2(t_commandes *start);

#endif

//<inf ls cat | ldj "afadfda"
//411121121112621112511111115