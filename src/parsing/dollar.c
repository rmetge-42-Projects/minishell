/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemma <bemma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:05:13 by rmetge            #+#    #+#             */
/*   Updated: 2025/06/02 15:46:00 by bemma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*dollar_arg(char *first, int i, int j, t_shell *shell)
{
	char	*arg;
	char	*path;

	if (i == 0)
		return (NULL);
	if (i == 1 && first[j] == '$' && first[j + 1] != 34 && first[j + 1] != 39)
		return (ft_strdup("$"));
	j++;
	i--;
	if (first + j && first + j + i - 1)
	{
		arg = ft_strndup(first + j, i);
		if (ft_strcmp(arg, "?") == 0)
			path = ft_itoa(shell->exit_code);
		else
			path = chr_path(arg, shell->enviro);
		free(arg);
	}
	else
		path = NULL;
	return (path);
}

char	*if_34(char *first, int *i, t_shell *shell)
{
	int		j;
	char	*f2;
	char	*arg;
	char	*before;
	int		len;

	arg = NULL;
	if (first[*i] && (first[*i] == 34 || first[*i] == 39))
	{
		j = 1;
		len = (*i) + j;
		before = ft_strndup(first, len);
		while (first[(*i) + j] && first[j + (*i)] != (first[(*i)]))
			j++;
		f2 = ft_substr(first, (*i), j);
		if (ft_strchr(f2, '$'))
			arg = ft_dollar(shell, f2 + 1, NULL);
		free(f2);
		(*i) += j;
	}
	if (arg)
	{
		f2 = space_join(arg, ft_strndup(first + (*i), 1));
		(*i)++;
		return (space_join(before, f2));
	}
	return (free(before), NULL);
}

char	*ft_before(char *first, t_shell *shell, int *i)
{
	char	*before;

	while (first[*i] && first[*i] != '$')
	{
		if (first[(*i)] && (first[(*i)] == 34 || first[(*i)] == 39)
			&& g_sig != 1)
		{
			before = if_34(first, i, shell);
			if (before)
				return (before);
		}
		else
			(*i)++;
	}
	if ((*i) != 0)
		return (ft_strndup(first, (*i)));
	return (NULL);
}

char	*ft_arg(char *first, t_shell *shell, int *i)
{
	char	*arg;
	int		x;
	int		j;

	x = 0;
	j = (*i);
	(*i) = 1;
	arg = NULL;
	if (first[j + (*i)])
	{
		while (first[j + (*i)]
			&& (ft_isalnum(first[j + (*i)]) || first[j + (*i)] == '_'))
			(*i)++;
		if (first[j + (*i)] && first[j + (*i)] == '?')
			(*i)++;
	}
	if (!arg && x == 0)
		arg = dollar_arg(first, (*i), j, shell);
	(*i) += j;
	return (arg);
}

char	*ft_dollar(t_shell *shell, char *first, char *dest)
{
	int		i;
	char	*before;
	char	*res;
	char	*arg;

	i = 0;
	arg = NULL;
	before = ft_before(first, shell, &i);
	if (first[i] && first[i] == '$')
		arg = ft_arg(first, shell, &i);
	res = space_join(dest, before);
	dest = space_join(res, arg);
	if (first [i])
		return (ft_dollar(shell, (first + i), dest));
	return (dest);
}
