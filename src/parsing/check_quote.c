/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemma <bemma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:23:44 by rmetge            #+#    #+#             */
/*   Updated: 2025/05/30 14:50:39 by bemma            ###   ########.fr       */
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
			if (enviro->value != NULL)
			{
				free(dollar);
				return (ft_strdup(enviro->value));
			}
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
		dest = ft_strjoin(s1, s2);
	else if (s1)
		dest = ft_strdup(s1);
	else if (s2)
		dest = ft_strdup(s2);
	else
		dest = NULL;
	free(s1);
	free(s2);
	return (dest);
}

t_token	*check_quote(t_shell *shell, int j, const char *s)
{
	enum e_token	arg_type;
	char			*first;
	char			*dest;

	arg_type = token_type(s, 0);
	first = ft_substr(s, 0, j);
	if ((arg_type == ARG || arg_type == QUOTE2) && ft_strchr(first, '$'))
	{
		dest = ft_dollar(shell, first, NULL);
		free(first);
		return (ft_tokennew(dest, arg_type));
	}
	return (ft_tokennew(first, arg_type));
}
