#include "minishell.h"

int	ft_isspace(char c)
{
	return (c == 32 || c == '\t' || c == '\v');
}

int	ft_isspecial(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == ';' || ft_isspace(c)
		|| c == '\'' || c == '\"' || c == '\0' || c == '$');
}

int	ft_ischar(void)