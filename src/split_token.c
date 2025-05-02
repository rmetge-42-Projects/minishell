/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmetge <rmetge@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:17:07 by rmetge            #+#    #+#             */
/*   Updated: 2025/05/02 10:47:56 by rmetge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

enum e_token	type(const char *s, int k)
{
	if (s[k] == '|')
		return (PIPE);
	else if (s[k] == '>' || s[k] == '<')
		return (REDIRECT);
	else if (s[k] == 39)
		return (QUOTE1);
	else if (s[k] == 34)
		return (QUOTE2);
	else
		return (ARG);
}

t_token	*ft_tokennew(char *value, enum e_token type)
{
	t_token	*token;

	token = (t_token *) malloc(sizeof(t_token));
	if (!token)
		return (NULL);
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
