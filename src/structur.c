/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structur.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmetge <rmetge@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 13:16:31 by rmetge            #+#    #+#             */
/*   Updated: 2025/05/02 10:43:27 by rmetge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_struc(char **path, char *cmd)
{
	t_list	*arg;

	(void)path;
	arg = ft_splitttt(cmd);
	if (arg == NULL)
		return (printf("Erreur\n"), 1);
	while (arg)
	{
		printf("%s\n", ((t_token *)arg->content)->value);
		printf("%i\n", ((t_token *)arg->content)->type);
		arg = arg->next;
	}
	return (0);
}
