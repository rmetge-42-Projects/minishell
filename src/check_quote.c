/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmetge <rmetge@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:23:44 by rmetge            #+#    #+#             */
/*   Updated: 2025/05/14 15:03:44 by rmetge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*dollar_no_first(t_shell *shell, char *dollar, int len, char *arg)
{
	char	*first;
	char	*if_d;
	int		l;
	int		i;

	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], arg, len) == 0)
		{
			l = (ft_strlen(shell->env[i]) - len);
			if_d = ft_substr(shell->env[i], (len + 1), l);
			first = ft_strjoin(dollar, if_d);
			free(if_d);
			free(dollar);
			free(arg);
			return (first);
		}
		i++;
	}
	free(arg);
	return (dollar);
}

char	*dollar_first(t_shell *shell, char *arg, int len)
{
	char	*dest;
	int		i;
	int		l;

	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], arg, len) == 0)
		{
			l = (ft_strlen(shell->env[i]) - len);
			dest = ft_substr(shell->env[i], (len + 1), l);
			free(arg);
			return (dest);
		}
		i++;
	}
	free(arg);
	dest = calloc(1, 1);
	dest[0] = '\0';
	return (dest);
}

char	*ft_dollar(t_shell *shell, char *first)
{
	char			*arg;
	int				i;
	int				len;
	char			*dollar;

	i = 0;
	arg = ft_strdup(ft_strrchr(first, '$') + 1);
	len = ft_strlen(arg);
	while (first[i] != '$')
		i++;
	if (i > 0)
	{
		i++;
		dollar = ft_calloc(i, 1);
		ft_strlcpy(dollar, first, i);
		return (dollar_no_first(shell, dollar, len, arg));
	}
	else
	{
		free(first);
		return (dollar_first(shell, arg, len));
	}
}

t_token	*check_quote(t_shell *shell, int j, const char *s)
{
	enum e_token	arg_type;
	char			*first;
	char			*dest;

	arg_type = token_type(s);
	if (s[0] == 34 || s[0] == 39)
		first = ft_substr(s, 1, j - 2);
	else
		first = ft_substr(s, 0, j);
	if ((arg_type == ARG || arg_type == QUOTE2) && ft_strchr(first, '$'))
	{
		dest = ft_dollar(shell, first);
		return (ft_tokennew(dest, arg_type));
	}
	return (ft_tokennew(first, arg_type));
}
