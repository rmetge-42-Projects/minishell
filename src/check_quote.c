/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmetge <rmetge@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:23:44 by rmetge            #+#    #+#             */
/*   Updated: 2025/05/20 18:54:20 by rmetge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	len_dollar(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && (ft_isalnum(arg[i]) || arg[i] == '_'))
		i++;
	return (i);
}

char	*chr_path(char *arg, t_env *enviro)
{
	char	*dollar;

	dollar = ft_calloc(len_dollar(arg) + 1, 1);
	ft_strlcpy(dollar, arg, len_dollar(arg) + 1);
	while (enviro)
	{
		if (ft_strcmp(dollar, enviro->key) == 0)
		{
			free(dollar);
			return (ft_strdup(enviro->value));
		}
		enviro = enviro->next;
	}
	free(dollar);
	return (NULL);
}

char	*space_join(char *s1, char *s2)
{
	char	*dest;

	if (s1 && s2)
	{
		dest = ft_strjoin(s1, s2);
		free(s1);
		free(s2);
	}
	else if (s1)
	{
		dest = s1;
		free(s2);
	}
	else if (s2)
	{
		dest = s2;
		free(s1);
	}
	else
	{
		dest = NULL;
		free(s1);
		free(s2);
	}
	return(dest);
}

char	*ft_dollar(t_shell *shell, char *first, char *dest)
{
	int	i;
	int	j;
	char	*before;
	char	*path;
	char	*arg;
	char	*res;
	char	*tmp;

	i = 0;
	before = NULL;
	res = NULL;
	tmp = NULL;
	while (first[i] && first[i] != '$')
		i++;
	before = ft_strndup(first, i);
	if (first[i])
		i++;
	j = i;
	i = 0;
	while (first[j + i] && (ft_isalnum(first[j + i]) || first[i] == '_'))
		i++;
	if (i == 0 && first[j - 1] == '$')
		path = ft_strdup("$");
	else
	{
		arg = ft_strndup(first + j, i);
		path = chr_path(arg, shell->enviro);
		free(arg);
	}
	res = space_join(dest, before);
	dest = space_join(res, path);
	if (first[j])
	{
		tmp = ft_dollar(shell, first + j + i, dest);
		dest = tmp;
	}
	return(dest);
}

t_token	*check_quote(t_shell *shell, int j, const char *s)
{
	enum e_token	arg_type;
	char			*first;
	char			*dest;

	arg_type = token_type(s);
	first = ft_substr(s, 0, j);
	if ((arg_type == ARG || arg_type == QUOTE2) && ft_strchr(first, '$'))
	{
		dest = ft_dollar(shell, first, NULL);
		free(first);
		return (ft_tokennew(dest, arg_type));
	}
	return (ft_tokennew(first, arg_type));
}
