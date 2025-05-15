/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmetge <rmetge@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:17:07 by rmetge            #+#    #+#             */
/*   Updated: 2025/05/15 12:06:10 by rmetge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

enum e_token	token_type(const char *s)
{
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
	if (c == ' ' || c == '\t' || c == '\n' || c == 39 || c == 34 || c == '|'
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
