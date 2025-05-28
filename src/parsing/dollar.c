/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmetge <rmetge@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:05:13 by rmetge            #+#    #+#             */
/*   Updated: 2025/05/28 18:25:04 by rmetge           ###   ########.fr       */
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
	char	*before;
	char	*res;

	i = 0;
	before = NULL;
	// if (first[i] == 39)
	// 	return (ft_strdup(first));
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
		else
			i++;
	}
	before = ft_strndup(first, i);
	// printf("%s\n", before);
	j = i;
	i = 0;
	if (first[j])
		i++;
	// if (first[j + 1] == 34 || first[j + 1] == 39)
	// {
	// 	// i = 1;
	// 	i++;
	// 	while (first[j + i] != first[j + 1])
	// 		i++;
	// 	j += i;
	// }
	while (first[j + i]
		&& (ft_isalnum(first[j + i]) || first[j + i] == '_'))
		i++;
	if (first[j + i] && first[j + i] == '?')
		i++;
	res = space_join(dest, before);
	dest = space_join(res, dollar_arg(first, i, j, shell));
	if (first[j + i])
		return (ft_dollar(shell, (first + j + i), dest));
	return (dest);
}
