/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemma <bemma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 11:25:05 by rmetge            #+#    #+#             */
/*   Updated: 2025/05/05 12:04:02 by bemma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	**ft_path(char **env)
// {
// 	int		i;
// 	char	**path;
// 	char	*tmp;

// 	i = 0;
// 	path = NULL;
// 	while (path == NULL)
// 	{
// 		if (ft_strncmp(env[i], "PATH", 4) == 0)
// 		{
// 			path = ft_split(env[i] + 5, ':');
// 			break ;
// 		}
// 		i++;
// 	}
// 	i = 0;
// 	while (path[i])
// 	{
// 		tmp = path[i];
// 		path[i] = ft_strjoin(path[i], "/");
// 		free(tmp);
// 		i++;
// 	}
// 	return (path);
// }
char	*find_path(char **envp, char *cmd)
{
	int		i;
	char	**path;
	char	*p_p;
	char	*full_cmd;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	path = ft_split(envp[i] + 5, ':');
	i = 0;
	while (path[i])
	{
		p_p = ft_strjoin(path[i], "/");
		full_cmd = ft_strjoin(p_p, cmd);
		free(p_p);
		if (access(full_cmd, X_OK) == 0)
		{
			ft_f_s(path);
			return (full_cmd);
		}
		free(full_cmd);
		i++;
	}
	ft_f_s(path);
	return (NULL);
}

