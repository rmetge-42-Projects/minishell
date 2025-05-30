/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemma <bemma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:05:13 by rmetge            #+#    #+#             */
/*   Updated: 2025/05/30 14:48:39 by bemma            ###   ########.fr       */
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

char	*ft_dollar(t_shell *shell, char *first, char *dest)
{
	int		i;
	int		j;
	char	*before;
	char	*res;
	char	*arg;
	char	*f2;
	int		x;

	i = 0;
	x = 0;
	before = NULL;
	arg = NULL;
	while (first[i] && first[i] != '$')
	{
		if (first[i] == 39)
		{
			j = 1;
			while (first[i + j] && first[j + i] != first[i])
				j++;
			j++;
			i += j;
		}
		else if (first[i] && first[i] == 34)
		{
			if (i != 0)
				before = ft_strndup(first, i);
			j = 1;
			while (first[i + j] && first[j + i] != 34)
				j++;
			i++;
			j--;
			f2 = ft_substr(first, i, j);
			if (ft_strchr(f2, '$'))
			{
				arg = ft_dollar(shell, f2, NULL);
				x = 1;
			}
			i += j + 1;
			j = 0;
			free(f2);
		}
		else
			i++;
	}
	if (arg == NULL && x == 0)
	{
		if (before)
		{
			free(before);
			before = NULL;
		}
		if (i != 0)
			before = ft_strndup(first, i);
		j = i;
		i = 0;
		if (first[j])
			i++;
		if (first[j + i] && first[j + i] == 34)
		{
			j++;
			while (first[i + j] && first[j + i] != 34)
				i++;
			f2 = ft_substr(first, j, i);
			arg = ft_dollar(shell, f2, NULL);
			free(f2);
		}
		else
		{
			while (first[j + i]
				&& (ft_isalnum(first[j + i]) || first[j + i] == '_'))
				i++;
			if (first[j + i] && first[j + i] == '?')
				i++;
		}
		if (!arg)
			arg = dollar_arg(first, i, j, shell);
	}
	res = space_join(dest, before);
	dest = space_join(res, arg);
	free(res);
	if (first[j + i])
		return (ft_dollar(shell, (first + j + i), dest));
	return (dest);
}

