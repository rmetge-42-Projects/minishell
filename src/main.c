/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemma <bemma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 11:02:57 by rmetge            #+#    #+#             */
/*   Updated: 2025/04/30 15:01:30 by bemma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_cmd *com = NULL;
	int i;

	com->argv[0] = "Makefile";
	com->argv[1] = "grep OBJ_DIR";
	com->argv[2] = "wc -l";
	com->argv[3] = "outfile";
	com->path = ft_path(env);
	// char **path;
	(void)argc;
	(void)argv;

	// path = ft_path(env);
	// char *cd = "ls cd  cat ";
	// ft_struc(path, "iubu uyi   8yg8gb ibbi '8yuguyv iuibi  uyuyvuygbuy' uyuyvuyg u");
	i = ft_pipex(com);
}