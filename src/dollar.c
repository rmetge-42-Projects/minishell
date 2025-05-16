/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmetge <rmetge@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:05:13 by rmetge            #+#    #+#             */
/*   Updated: 2025/05/16 17:21:36 by rmetge           ###   ########.fr       */
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


char	*ft_dollar(t_shell *shell, char *first)
{
	char			*arg;
	int				i;
	char			*dollar;
	char	*befor;
	char	*after;
	char	*tmp;
	int		len;
	int		j;
	char	*res;

	i = 0;
	befor = NULL;
	after = NULL;
	arg = ft_strdup(ft_strchr(first, '$') + 1);
	// if (ft_strchr(arg, '$') != NULL)

	dollar = chr_path(arg, shell->enviro);
	while (first[i] != '$')
		i++;
	if (i != 0)
		befor = ft_strndup(first, i);
	if ((i + len_dollar(arg)) < (int)ft_strlen(arg))
	{
		j = 0;
		len = len_dollar(arg);
		if (arg[len] == 34 || arg[len] == 39)
		{
			j = 1;
			len++;
		}
		after = ft_strndup(arg + len, ft_strlen(arg) - len - j);
	}
	if (befor && dollar)
	{
		tmp = ft_strjoin(befor, dollar);
		free(dollar);
		dollar = tmp;
		free(befor);
		befor = NULL;
	}
	if (after && dollar)
	{
		tmp = ft_strjoin(dollar, after);
		free(dollar);
		dollar = tmp;
		free(after);
	}
	if (befor)
		return(befor);
	return(dollar);
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