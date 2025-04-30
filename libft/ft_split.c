/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmetge <rmetge@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 10:17:05 by rmetge            #+#    #+#             */
/*   Updated: 2025/01/30 10:53:41 by rmetge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	ft_contword(char const *s, char c)
{
	int	nbr;
	int	in_word;

	nbr = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && !in_word)
		{
			in_word = 1;
			nbr++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (nbr);
}

void	*ft_free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (NULL);
}

static void	ft_process(char const *s, char c, int *j, int *k)
{
	while (s[*j] == c && s[*j])
		(*j)++;
	*k = *j;
	while (s[*j] != c && s[*j])
		(*j)++;
}

char	**ft_split(char const *s, char c)
{
	int		nbr;
	char	**dest;
	int		i;
	int		j;
	int		k;

	nbr = ft_contword(s, c);
	dest = (char **)malloc((nbr + 1) * sizeof(char *));
	if (!dest)
		return (NULL);
	i = 0;
	j = 0;
	k = 0;
	while (s[j])
	{
		ft_process(s, c, &j, &k);
		if (k < j)
		{
			dest[i++] = ft_substr(s, (size_t)k, (size_t)(j - k));
			if (!dest[i -1])
				return (ft_free_split(dest));
		}
	}
	dest[i] = 0;
	return (dest);
}
