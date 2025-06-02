/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmetge <rmetge@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:05:13 by rmetge            #+#    #+#             */
/*   Updated: 2025/06/02 14:16:14 by rmetge           ###   ########.fr       */
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

	arg = NULL;
	if (first[*i] && first[*i] == 34)
	{
		(*i)++;
		if (i != 0)
			before = ft_strndup(first, (*i));
		j = 0;
		while (first[(*i) + j] && first[j + (*i)] != 34)
			j++;
		// (*i)++;
		j++;
		f2 = ft_substr(first, (*i), j);
		if (ft_strchr(f2, '$'))
			arg = ft_dollar(shell, f2, NULL);
		(*i) += j;
		j = 0;
		free(f2);
	}
	if (arg)
		return (space_join(before, arg));
	return (free(before), NULL);
}

char	*ft_before(char *first, t_shell *shell, int *i)
{
	int		j;
	char	*before;

	while (first[*i] && first[*i] != '$')
	{
		if (first[*i] == 39)
		{
			j = 1;
			while (first[(*i) + j] && first[j + (*i)] != first[(*i)])
				j++;
			j++;
			(*i) += j;
		}
		else if (first[(*i)] && first[(*i)] == 34)
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
	// printf("before === %s\n", before);
	if (first[i] && first[i] == '$')
		arg = ft_arg(first, shell, &i);
	// printf("arg === %s\n", arg);
	res = space_join(dest, before);
	dest = space_join(res, arg);
	// printf("dest === %s\n", dest);
	if (first [i])
		return (ft_dollar(shell, (first + i), dest));
	return (dest);
}
