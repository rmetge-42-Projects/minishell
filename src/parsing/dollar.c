/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmetge <rmetge@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:05:13 by rmetge            #+#    #+#             */
/*   Updated: 2025/05/29 14:20:55 by rmetge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*dollar_arg(char *first, int i, int j, t_shell *shell)
{
	char	*arg;
	char	*path;

	// if ((first[j] == '$') && (first[j] == 34 || first[j] == 39))
	// 	return (NULL);
		// path = ft_strdup("$");
	// else
	// {
	if (i == 1 && first[j] == '$' && first[j + 1] != 34 && first[j + 1] != 39)
		return (ft_strdup("$"));
	j++;
	i--;
	// printf("bef pth %s\n", first + j);
	arg = ft_strndup(first + j, i);
	if (ft_strcmp(arg, "?") == 0)
		path = ft_itoa(shell->exit_code);
	else
		path = chr_path(arg, shell->enviro);
	free(arg);
	// }
	return (path);
}

char	*ft_dollar(t_shell *shell, char *first, char *dest)
{
	int		i;
	int		j;
	// int		k;
	char	*before;
	char	*res;
	char	*arg;
	// char	*tmp;
	char *f2;

	i = 0;
	before = NULL;
	arg = NULL;
	// printf("%s\n", first);
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
			before = ft_strndup(first, i);
			j = 1;
			// k = i;
			while (first[i + j] && first[j + i] != 34)
				j++;
			// j++;
			i++;
			j--;
			f2 = ft_substr(first, i, j);
			// f2 = ft_strdup("$");
			// printf("f2 = %s\n", f2);
			// return (NULL);
			if (ft_strchr(f2, '$'))
			{
				arg = ft_dollar(shell, f2, NULL);
				// i += j + 1;
			}
			else
			{
				free(before);
				before = NULL;
			}
			i += j + 1;
			j = 0;
			free(f2);
		}
		else
			i++;
	}
	if (arg == NULL)
	{
		if (!before)
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
		if (!arg)
			arg = dollar_arg(first, i, j, shell);
	}
	res = space_join(dest, before);
	dest = space_join(res, arg);
	if (first[j + i])
		return (ft_dollar(shell, (first + j + i), dest));
	return (dest);
}
