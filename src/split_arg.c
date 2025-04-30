/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmetge <rmetge@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:41:25 by rmetge            #+#    #+#             */
/*   Updated: 2025/04/30 09:02:31 by rmetge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_contword(char const *s)
{
	int	nbr;
	int	in_word;
	int	cote[2];

	nbr = 0;
	in_word = 0;
	cote[0] = 0;
	cote[1] = 1;
	while (*s)
	{
		if (*s == 39 && cote[0] == 0)
			cote[0] = 1;
		else if (*s == 39 && cote[0] == 1)
			cote[0] = 0;
		if ((*s != ' ' || *s != '\t' || *s != '\n') && !in_word && cote[0] == 0)
		{
			in_word = 1;
			nbr++;
		}
		else if ((*s == ' ' || *s == '\t' || *s == '\n') && cote[0] == 0)
			in_word = 0;
		s++;
	}
	// if (cote[0] == 1)
	// 	return (0);
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

static void	ft_process(char const *s, int *j, int *k)
{
	int	cote[2];

	cote[0] = 0;
	cote[1] = 1;
	while ((s[*j] == ' ' || s[*j] == '\t' || s[*j] == '\n' || s[*j] == 39) && s[*j])
	{
		if ()
		(*j)++;
	}
	*k = *j;
	while ((s[*j] != ' ' && s[*j] != '\t' && s[*j] != '\n') && s[*j])
		(*j)++;

}

char	**ft_splitttt(char const *s)
{
	int		nbr;
	char	**dest;
	int		i;
	int		j;
	int		k;

	nbr = ft_contword(s);
	if(nbr == 0)
		// {printf("%i\n", nbr);
		// return (NULL);}
	dest = (char **)malloc((nbr + 1) * sizeof(char *));
	if (!dest)
		return (NULL);
	i = 0;
	j = 0;
	k = 0;
	while (s[j])
	{
		ft_process(s, &j, &k);
		// printf("%i et %i\n", k, (j - k));
		if (k < j)
		{
			dest[i++] = ft_substr(s, (size_t)k, (size_t)(j - k));
			if (!dest[i -1])
				return (ft_free_split(dest));
			// printf("%i\n", i);
			// printf("%s\n", dest[i - 1]);
		}
	}
	dest[i] = 0;
	return (dest);
}
