/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmetge <rmetge@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 11:25:05 by rmetge            #+#    #+#             */
/*   Updated: 2025/05/06 15:39:40 by rmetge           ###   ########.fr       */
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

char	*ft_find_path(char **path, char *argv)
{
	int		i;
	char	*path1;
	char	**str;

	i = 0;
	if (ft_strchr(argv, '/') != 0)
	{
		if (access(argv, X_OK) == 0)
			return (ft_strdup(argv));
	}
	str = ft_split(argv, ' ');
	while (path[i])
	{
		path1 = ft_strjoin(path[i], str[0]);
		if (access(path1, X_OK) == 0)
			return (ft_free_split(str), path1);
		i++;
		free(path1);
	}
	return (ft_free_split(str), NULL);
}
