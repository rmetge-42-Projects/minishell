/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmetge <rmetge@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:05:13 by rmetge            #+#    #+#             */
/*   Updated: 2025/05/28 15:19:20 by rmetge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*dollar_arg(char *first, int i, int j, t_shell *shell)
{
	char	*arg;
	char	*path;

	if (i == 0 && first[j - 1] == '$' && first[j] != 34 && first[j] != 39)
		path = ft_strdup("$");
	else
	{
		arg = ft_strndup(first + j, i);
		if (ft_strcmp(arg, "?") == 0)
			path = ft_itoa(shell->exit_code);
		else
			path = chr_path(arg, shell->enviro);
		free(arg);
	}
	return (path);
}

char	*ft_dollar(t_shell *shell, char *first, char *dest)
{
	int		i;
	int		j;
	char	*before;
	char	*res;

	i = 0;
	if (first[i] == 34)
		return (first);
	while (first[i] && first[i] != '$')
		i++;
	before = ft_strndup(first, i);
	if (first[i])
		i++;
	j = i;
	i = 0;
	while (first[j + i]
		&& (ft_isalnum(first[j + i]) || first[j + i] == '_'))
		i++;
	if (first[j + 0] == '?')
		i++;
	res = space_join(dest, before);
	dest = space_join(res, dollar_arg(first, i, j, shell));
	if (first[j + i])
		return (ft_dollar(shell, (first + j + i), dest));
	return (dest);
}
