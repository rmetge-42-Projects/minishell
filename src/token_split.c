/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmetge <rmetge@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:41:25 by rmetge            #+#    #+#             */
/*   Updated: 2025/05/14 11:43:25 by rmetge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static void	process_quote2(char const *s, int *j)
{
	if (s[*j] == '|')
		(*j)++;
	else if (s[*j] == '<')
	{
		(*j)++;
		if (s[*j] == '<')
			(*j)++;
	}
	else if (s[*j] == '>')
	{
		(*j)++;
		if (s[*j] == '>')
			(*j)++;
	}
}

static void	ft_process_2(char const *s, int *j, int *quote)
{
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
	else if (quote[2] == 1)
		process_quote2(s, j);
	else
	{
		while (chr_sep(s[*j]) == 0 && s[*j])
			(*j)++;
	}
}

static void	ft_process(char const *s, int *j, int *k)
{
	int	quote[3];

	quote[0] = 0;
	quote[1] = 0;
	quote[2] = 0;
	while (chr_sep(s[*j]) == 1 && quote[0] == 0 && quote[1] == 0
		&& quote[2] == 0 && s[*j])
	{
		if (s[*j] == 39)
			quote[0] = 1;
		else if (s[*j] == 34)
			quote[1] = 1;
		else if (s[*j] == '|' || s[*j] == '<' || s[*j] == '>')
			quote[2] = 1;
		else
			(*j)++;
	}
	*k = *j;
	ft_process_2(s, j, quote);
}

static int	check_all_quote(char *s)
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
		else if (quote[0] == 1 && s[i] == 34)
			quote[0] = 0;
		else if (quote[1] == 1 && s[i] == 39)
			quote[1] = 0;
		i++;
	}
	if (quote[0] == 1 || quote[1] == 1)
		return (1);
	else
		return (0);
}

t_list	*stuctur_token(char const *s, t_shell *shell)
{
	int		j;
	int		k;
	t_list	*dest;
	t_token	*t;

	dest = NULL;
	if (check_all_quote((char *)s) == 1)
		return (NULL);
	j = 0;
	k = 0;
	while (s[j])
	{
		ft_process(s, &j, &k);
		if (k < j)
		{
			t = check_quote(shell, j - k, s + k);
			// if (t != NULL)
			// 	break;
			ft_lstadd_back(&dest, ft_lstnew((t)));
		}
	}
	return (dest);
}
