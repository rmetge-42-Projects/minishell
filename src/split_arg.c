/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmetge <rmetge@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:41:25 by rmetge            #+#    #+#             */
/*   Updated: 2025/04/30 13:57:52 by rmetge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	chr_sep(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == 39 /*|| c == 34*/)
		return (1);
	return (0);
}

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
		if (cote[1] == 0)
		{
			if (*s == 39 && cote[0] == 0)
				cote[0] = 1;
			else if (*s == 39 && cote[0] == 1)
				cote[0] = 0;
		}
		// else if (cote[0] == 0)
		// {
		// 	if (*s == /*34*/'*' && cote[1] == 0)
		// 		cote[1] = 1;
		// 	else if (*s == /*34*/'*' && cote[1] == 1)
		// 		cote[1] = 0;
		// }
		if (chr_sep(*s) == 0 && !in_word && cote[0] == 0 /*&& cote[1] == 0*/)
		{
			in_word = 1;
			nbr++;
		}
		else if (chr_sep(*s) == 1 && cote[0] == 0 /*&& cote[1] == 0*/)
			in_word = 0;
		s++;
	}
	if (cote[0] == 1 /*|| cote[1] == 1*/ )
		return (0);
	return (nbr);
}


static void	ft_process(char const *s, int *j, int *k)
{
	int	cote[2];

	cote[0] = 0;
	cote[1] = 1;
	while ((chr_sep(s[*j]) == 1 && cote[0] == 0 /*|| cote[1] == 0 */)&& s[*j])
	{
		if (s[*j + 1] == 39)
			cote[0] = 1;
		// else if (s[*j + 1] == /*34*/'*')
		// 	cote[1] = 1;
		(*j)++;
	}
	*k = *j;
	// printf("%i\n\n\n\n", cote[0]);
	if (cote[0] == 1)
	{
		(*j)++;
		while (s[*j] != 39)
			(*j)++;
		(*j)++;
		// printf("1\n");
	}
	// if (cote[1] == 1)
	// {
	// 	(*j)++;
	// 	while (s[*j] != /*34*/'*')
	// 		(*j)++;
	// 	(*j)++;
	// 	// printf("1\n");
	// }
	else
	{
		while (chr_sep(s[*j]) == 0 && s[*j])
			(*j)++;
	}

}

char	**ft_splitttt(char const *s)
{
	int		nbr;
	char	**dest;
	int		i;
	int		j;
	int		k;

	nbr = ft_contword(s);
	printf("%i\n", nbr);
	if(nbr == 0)
		return (NULL);
	dest = (char **)malloc((nbr + 1) * sizeof(char *));
	if (!dest)
		return (NULL);
	i = 0;
	j = 0;
	k = 0;
	while (s[j])
	{
		ft_process(s, &j, &k);
		printf("%i et %i\n", k, j);
		if (k < j)
		{
			dest[i++] = ft_substr(s, (size_t)k, (size_t)(j - k));
			if (!dest[i -1])
				return (ft_free_split(dest));
			printf("%i\n", i);
			printf("%s\n\n", dest[i - 1]);
		}
	}
	dest[i] = 0;
	return (dest);
}
