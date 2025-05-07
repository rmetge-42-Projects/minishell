/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmetge <rmetge@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:17:07 by rmetge            #+#    #+#             */
/*   Updated: 2025/05/06 15:59:40 by rmetge           ###   ########.fr       */
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

	token = (t_token *) ft_calloc(1, sizeof(t_token));
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

int	check_token(t_shell *shell)
{
	int		cmd;
	t_list	*tmp;

	tmp = shell->tokens;
	cmd = 0;
	while (shell->tokens)
	{
		if (((t_token *)shell->tokens->content)->type == PIPE)
		{
			if (!shell->tokens->next
				|| ((t_token *)shell->tokens->next->content)->type == PIPE
				|| cmd == 0)
				return (1);
			cmd = 0;
		}
		else if (((t_token *)shell->tokens->content)->type == REDIRECT)
		{
			if (!shell->tokens->next
				|| ((t_token *)shell->tokens->next->content)->type == PIPE
				|| ((t_token *)shell->tokens->next->content)->type == REDIRECT)
				return (1);
		}
		else
			cmd = 1;
		shell->tokens = shell->tokens->next;
	}
	shell->tokens = tmp;
	return (0);
}
