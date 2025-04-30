/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemma <bemma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 11:25:05 by rmetge            #+#    #+#             */
/*   Updated: 2025/04/30 11:29:31 by bemma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_path(char **env)
{
	int		i;
	char	**path;
	char	*tmp;

	i = 0;
	path = NULL;
	while (path == NULL)
	{
		if (ft_strncmp(env[i], "PATH", 4) == 0)
		{
			path = ft_split(env[i] + 5, ':');
			break ;
		}
		i++;
	}
	i = 0;
	while (path[i])
	{
		tmp = path[i];
		path[i] = ft_strjoin(path[i], "/");
		free(tmp);
		i++;
	}
	return (path);
}