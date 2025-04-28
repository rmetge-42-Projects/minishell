/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structur.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmetge <rmetge@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 13:16:31 by rmetge            #+#    #+#             */
/*   Updated: 2025/04/28 16:34:50 by rmetge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_cmd	struc_cmd(char **path)
// {
// 	t_cmd	cmd;

// 	return (cmd);
// }

int	ft_struc(char **path, char *cmd)
{
	// t_cmd	cmd;

	//cmd = struc_cmd(path);
	(void)path;
	int i = 0;
	char **arg;
	arg = ft_splitttt(cmd);
	while (arg[i])
	{
		printf("%s\n", arg[i]);
		i++;
	}
	return (0);
}