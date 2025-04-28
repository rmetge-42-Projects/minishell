/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmetge <rmetge@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 11:02:57 by rmetge            #+#    #+#             */
/*   Updated: 2025/04/28 16:14:53 by rmetge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char **path;
	(void)argc;
	(void)argv;

	path = ft_path(env);
	// char *cd = "ls cd  cat ";
	ft_struc(path, "iubu uyi   8yg8gb ibbi '8yuguyv iuibi  uyuyvuygbuy' uyuyvuyg u");
}