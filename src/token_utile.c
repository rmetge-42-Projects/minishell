/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmetge <rmetge@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:17:07 by rmetge            #+#    #+#             */
/*   Updated: 2025/05/13 19:23:35 by rmetge           ###   ########.fr       */
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

t_token	*check_quote(t_shell *shell, int j, const char *s)
{
	int				d;
	enum e_token	arg_type;
	char			*arg;
	char			*dollard;
	int				len;
	char			*first;
	char			*if_d;

	d = 0;
	arg = NULL;
	arg_type = token_type(s);
	if (s[0] == 34 || s[0] == 39)
		first = ft_substr(s, 1, j - 2);
	else
		first = ft_substr(s, 0, j);
	if ((arg_type == ARG || arg_type == QUOTE2) && ft_strchr(first, '$') != NULL)
	{
		arg = ft_strdup(ft_strrchr(first, '$') + 1);
		len = ft_strlen(arg);
		while (first[d] != '$')
			d++;
		if (d > 0)
		{
			d++;
			dollard = ft_calloc(d , 1);
			ft_strlcpy(dollard, first, d);
			free(first);
			d = 0;
			while (shell->env[d])
			{
				if (ft_strncmp(shell->env[d], arg, len) == 0)
				{
					if_d = ft_substr(shell->env[d], (len + 1), (ft_strlen(shell->env[d]) - len));
					first = ft_strjoin(dollard, if_d);
					free(if_d);
					free(dollard);
					free(arg);
					return (ft_tokennew(first, arg_type));
				}
				d++;
			}
			free(arg);
			return (ft_tokennew(dollard, arg_type));
			free(dollard);
		}
		else
		{
			free(first);
			d = 0;
			while (shell->env[d])
			{
				if (ft_strncmp(shell->env[d], arg, len) == 0)
					first = ft_substr(shell->env[d], (len + 1), (ft_strlen(shell->env[d]) - len));
				d++;
			}
		}
		free(arg);
	}
	return (ft_tokennew(first, arg_type));
}
