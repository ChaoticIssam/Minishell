#include "minishell.h"

ç

int	ft_isspecial(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == ';' || ft_isspace(c)
		|| c == '\'' || c == '\"' || c == '\0' || c == '$');
}

