/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structur.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmetge <rmetge@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 13:16:31 by rmetge            #+#    #+#             */
/*   Updated: 2025/04/30 19:00:40 by rmetge           ###   ########.fr       */
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
	//int i = 0;
	t_list	*arg;
	arg = ft_splitttt(cmd);
	if (arg == NULL)
		return(printf("Erreur\n"), 1);
	while (arg)
	{
		printf("%s\n", (char *)arg->content);
		arg = arg->next;
	}
	return (0);
}