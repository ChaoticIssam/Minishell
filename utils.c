/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iszitoun <iszitoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 22:58:59 by iszitoun          #+#    #+#             */
/*   Updated: 2023/06/18 16:04:09 by iszitoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strncmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s2[i] || s1[i])
	{
		if (s2[i] != s1[i])
			return (s2[i] - s1[i]);
		i++;
	}
	return (0);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

void	ft_putstr(char *str)
{
	printf("%s", str);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*x;
	int		i;
	int		j;
	int		s1_len;
	int		s2_len;

	j = 0;
	i = 0;
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	x = malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!x)
		return (0);
	while (s1[i])
	{
		x[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		x[i] = s2[j];
		i++;
		j++;
	}
	x[i] = '\0';
	return (x);
}
