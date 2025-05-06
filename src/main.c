/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmetge <rmetge@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 11:02:57 by rmetge            #+#    #+#             */
/*   Updated: 2025/05/06 15:42:20 by rmetge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*mini;
	t_shell	*shell;

	(void)argc;
	(void)argv;
	shell = ft_calloc(1, sizeof(t_shell));
	shell->path = ft_path(env);
	while (1)
	{
		mini = readline("minishell >");
		ft_structur(shell, mini);
	}
}
