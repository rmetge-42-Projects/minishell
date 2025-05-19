/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmetge <rmetge@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:05:13 by rmetge            #+#    #+#             */
/*   Updated: 2025/05/19 18:59:10 by rmetge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	before_after(char **dollar, char **str, int i)
{
	char	*tmp;

	tmp = NULL;
	if (i == 1)
		tmp = ft_strjoin((*str), (*dollar));
	else if (i == 2)
		tmp = ft_strjoin((*dollar), (*str));
	free(*dollar);
	*dollar = tmp;
	free(*str);
	*str = NULL;
	// printf("%s\n", dollar);
}

// char	*after(char *first, char *arg)
// {
// 	int		j;
// 	int		len;

// 	j = 0;
// 	len = len_dollar(arg);
// 	if (arg[len] == 34 || arg[len] == 39)
// 	{
// 		j = 1;
// 		len++;
// 	}
// 	after = ft_strndup(arg + len, ft_strlen(arg) - len - j);
// }

char	*dollar_path(char *arg, t_env *enviro, char *first)
{
	char	*dollar;
	int		i;
	int		len;
	char	*before;
	char	*after;
	int		j;


	// int		k;

	// while
	// k = len_dollar(ft_strchr(first, '$') + 1);
	// arg = ft_strndup(ft_strchr(first, '$') + 1, k);
	i = 0;
	before = NULL;
	after = NULL;
	dollar = chr_path(arg, enviro);
	while (first[i] != '$')
		i++;
	if (i > 0)
		before = ft_strndup(first, i);
	if ((i + len_dollar(arg) + 1) < (int)ft_strlen(arg))
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
	printf("%s\n", after);
	if (before && dollar)
		before_after(&dollar, &before, 1);
	if (after && dollar)
		before_after(&dollar, &after, 2);
	// printf("%s\n", dollar);
	if (before)
		return(before);
	return (dollar);
}
