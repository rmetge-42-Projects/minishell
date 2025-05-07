/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmetge <rmetge@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:17:07 by rmetge            #+#    #+#             */
/*   Updated: 2025/05/07 14:40:51 by rmetge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

enum e_token	token_type(const char *s, int k)
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

t_token	*check_quote(t_shell *shell, int k, int j, char *s)
{
	int				i;
	int				d;
	t_token			*t;
	enum e_token	arg_type;
	char			*arg;
	char			*dollard;

	i = j - k;
	d = 0;
	arg_type = token_type(s, k);
	if (arg_type == ARG && s[k] == '$')
	{
		arg = ft_substr(s, k + 1, i - 2);
		while (shell->env[d])
		{
			if (ft_strncmp(shell->env[d], arg, ft_strlen(arg)) == 0)
			{
				dollard = ft_substr(shell->env[d], ft_strlen(arg), ft_strlen(shell->env[d] - ft_strlen(arg)));
				return (ft_tokennew(dollard, arg_type));;
			}
			j++;
		}
	}
	else if (arg_type == QUOTE1 && s[k + 1] == '$')
	{
		arg = ft_substr(s, k + 1, i - 2);
		while (shell->env[d])
		{
			if (ft_strncmp(shell->env[d], arg, ft_strlen(arg)) == 0)
			{
				dollard = ft_substr(shell->env[d], ft_strlen(arg), ft_strlen(shell->env[d] - ft_strlen(arg)));
				return (ft_tokennew(dollard, arg_type));
			}
			j++;
		}
	}
	if (s[k] == 34 || s[k] == 39)
		return (ft_tokennew(ft_substr(s, k + 1, i - 2), arg_type));
	else
		return (ft_tokennew(ft_substr(s, k, i), arg_type));
}
