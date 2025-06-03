/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemma <bemma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:41:25 by rmetge            #+#    #+#             */
/*   Updated: 2025/06/03 14:36:15 by bemma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_redir(char const *s, int *j)
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

void	ft_process_2(char const *s, int *j, int redir)
{
	if (s[*j] == 39 || s[*j] == 34)
		ft_process_quote(s, j, s[*j]);
	else if (redir == 1)
		process_redir(s, j);
	else
	{
		while (s[*j] && chr_sep(s[*j]) == 0)
		{
			if (s[*j] && (s[*j] == 39 || s[*j] == 34))
				ft_process_2(s, j, redir);
			else
				(*j)++;
		}
	}
}

static void	ft_process(char const *s, int *j, int *k)
{
	int	redir;

	redir = 0;
	while (chr_sep(s[*j]) == 1 && redir == 0 && s[*j])
	{
		if (s[*j] == '|' || s[*j] == '<' || s[*j] == '>')
			redir = 1;
		else
			(*j)++;
	}
	*k = *j;
	ft_process_2(s, j, redir);
}

int	check_all_quote(char *s)
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
			if (t->value != NULL)
				ft_lstadd_back(&dest, ft_lstnew((t)));
			else
				free_tokens(t);
		}
	}
	return (dest);
}
