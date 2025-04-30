/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmetge <rmetge@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:41:25 by rmetge            #+#    #+#             */
/*   Updated: 2025/04/30 18:52:25 by rmetge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	chr_sep(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == 39 || c == 34)
		return (1);
	return (0);
}

//static void	ft_process_2

static void	ft_process(char const *s, int *j, int *k)
{
	int	quote[2];

	quote[0] = 0;
	quote[1] = 0;
	while (chr_sep(s[*j]) == 1 && quote[0] == 0 && quote[1] == 0 && s[*j])
	{
		if (s[*j + 1] == 39)
			quote[0] = 1;
		else if (s[*j + 1] == 34)
			quote[1] = 1;
		(*j)++;
	}
	*k = *j;
	if (quote[0] == 1)
	{
		(*j)++;
		while (s[*j] != 39)
			(*j)++;
		(*j)++;
	}
	else if (quote[1] == 1)
	{
		(*j)++;
		while (s[*j] != 34)
			(*j)++;
		(*j)++;
	}
	else
	{
		while (chr_sep(s[*j]) == 0 && s[*j])
			(*j)++;
	}
}

int	chek_quote(char *s)
{
	int	quote[2];
	int	i;

	quote[0] = 0;
	quote[1] = 0;
	i = 0;

	while (s[i])
	{
		if (s[i] == 34 && quote[1] == 0 && quote[0] == 0)
			quote[0] = 1;
		else if (s[i] == 39 && quote[0] == 0 && quote[1] == 0)
			quote[1] = 1;
		else if(quote[0] == 1 && s[i] == 34)
			quote[0] = 0;
		else if(quote[1] == 1 && s[i] == 39)
			quote[1] = 0;
		i++;
	}
	if (quote[0] == 1 || quote[1] == 1)
		return(1);
	else
		return(0);
}


t_list	*ft_splitttt(char const *s)
{
	int		j;
	int		k;
	t_list	*dest;

	dest = NULL;
	if (chek_quote((char *)s) == 1)
		return(dest);
	j = 0;
	k = 0;
	while (s[j])
	{
		ft_process(s, &j, &k);
		if (k < j)
			ft_lstadd_back(&dest, ft_lstnew(ft_substr(s, (size_t)k, (size_t)(j - k))));
	}
	return (dest);
}
