/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemma <bemma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:05:13 by rmetge            #+#    #+#             */
/*   Updated: 2025/05/30 14:51:06 by bemma            ###   ########.fr       */
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
	if (first + j && first +j + i - 1)
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
	int	j;
	char	*f2;
	char	*arg;
	char	*before;

	arg = NULL;
	if (first[*i] && first[*i] == 34)
	{
		if (i != 0)
			before = ft_strndup(first, (*i));
		j = 1;
		while (first[(*i) + j] && first[j + (*i)] != 34)
			j++;
		(*i)++;
		j--;
		f2 = ft_substr(first, (*i), j);
		if (ft_strchr(f2, '$'))
		{
			arg = ft_dollar(shell, f2, NULL);
		}
		(*i) += j + 1;
		j = 0;
		free(f2);
	}
	if (arg)
		return (space_join(before, arg));
	free(before);
	return (NULL);
}

char	*ft_before(char *first, t_shell *shell, int *i)
{
	int		j;
	char	*before;

	before = NULL;
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
				return(before);
		}
		else
		(*i)++;
	}
	if ((*i) != 0)
		return (ft_strndup(first, (*i)));
	return (NULL);
}


char	*ft_dollar(t_shell *shell, char *first, char *dest)
{
	int		i;
	int		j;
	char	*before;
	char	*res;
	char	*arg;
	char	*f2;

	i = 0;
	j = 0;
	// before = NULL;
	arg = NULL;
	// if (first == NULL)
	// 	return (NULL);
	before = ft_before(first, shell, &i);
	// printf("bef =%s\n", before);v
	if (first[j] && first[j] == '$')
	{
		j = i;
		i = 1;
		if (first[j + i])
		{
			if (first[j + i] == 34)
			{
				j++;
				while (first[i + j] && first[j + i] != 34)
					i++;
				f2 = ft_substr(first, j, i);
				// printf("%s\n", f2);
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
		}
		if (!arg)
			arg = dollar_arg(first, i, j, shell);
	}
	res = space_join(dest, before);
	dest = space_join(res, arg);
	if (first [j + i])
		return (ft_dollar(shell, (first + j + i), dest));
	return (dest);
}

