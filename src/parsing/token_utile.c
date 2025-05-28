/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmetge <rmetge@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:17:07 by rmetge            #+#    #+#             */
/*   Updated: 2025/05/28 15:51:19 by rmetge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

enum e_token	token_type(const char *s)
{
	int	i;

	i = 0;
	if (s[i] == 39 && s[i + 1] == 39)
		token_type(s + 2);
	if (s[0] == '|')
		return (PIPE);
	else if (s[0] == '>' || s[0] == '<')
		return (REDIRECT);
	else if (s[0] == 39)
		return (QUOTE1);
	else if (s[0] == 34)
		return (QUOTE2);
	else
		return (ARG);
}

t_token	*ft_tokennew(char *value, enum e_token type)
{
	t_token	*token;

	token = (t_token *) ft_calloc(1, sizeof(t_token));
	if (!token)
		return (free(token), NULL);
	token->value = value;
	token->type = type;
	return (token);
}

int	chr_sep(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '|'
		|| c == '<' || c == '>')
		return (1);
	return (0);
}

int	check_token(t_list *token)
{
	int		cmd;

	cmd = 0;
	while (token)
	{
		if (((t_token *)token->content)->type == PIPE)
		{
			if (!token->next || ((t_token *)token->next->content)->type == PIPE
				|| cmd == 0)
				return (1);
			cmd = 0;
		}
		else if (((t_token *)token->content)->type == REDIRECT)
		{
			if (!token->next || ((t_token *)token->next->content)->type == PIPE
				|| ((t_token *)token->next->content)->type == REDIRECT)
				return (1);
		}
		else
			cmd = 1;
		token = token->next;
	}
	return (0);
}

void	ft_process_quote(char const *s, int *j, char sep)
{
	(*j)++;
	while (s[*j] && s[*j] != sep)
		(*j)++;
	(*j)++;
	if (s[*j] != ' ')
		ft_process_2(s, j, 0);
}
