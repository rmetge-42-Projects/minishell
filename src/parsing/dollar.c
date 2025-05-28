/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemma <bemma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:05:13 by rmetge            #+#    #+#             */
/*   Updated: 2025/05/28 14:57:46 by bemma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*dollar_arg(char *first, int i, int j, t_shell *shell)
{
	char	*arg;
	char	*path;

	// printf("first = %c\n", first[j]);
	if (i == 0 && first[j - 1] == '$')
		path = ft_strdup("$");
	else if (first[j] == '?')
		path = ft_itoa(shell->exit_code);
	else
	{
		arg = ft_strndup(first + j, i);
		path = chr_path(arg, shell->enviro);
		free(arg);
	}
	// printf("doll = %s\n", path);
	return (path);
}

char	*ft_dollar(t_shell *shell, char *first, char *dest)
{
	int		i;
	int		j;
	char	*before;
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
	if (first[j + i] == '?')
		i++;
	else
	{
		while (first[j + i] && (ft_isalnum(first[j + i]) || first[j + i] == '_'))
			i++;
	}
	res = space_join(dest, before);
	dest = space_join(res, dollar_arg(first, i, j, shell));
	if (first[j + i])
		return (ft_dollar(shell, (first + j + i), dest));
	return (dest);
}
