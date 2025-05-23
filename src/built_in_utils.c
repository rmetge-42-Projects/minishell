/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmetge <rmetge@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 09:14:50 by rmetge            #+#    #+#             */
/*   Updated: 2025/05/22 20:15:51 by rmetge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_echo(t_shell *shell, int newline)
{
	int	i;
	int	j;

	i = 1;
	while (shell->cmd->argv[i] != NULL
		&& ft_strncmp(shell->cmd->argv[i], "-n", 2) == 0)
	{
		j = 2;
		while (shell->cmd->argv[i][j] == 'n')
			j++;
		if (!shell->cmd->argv[i][j])
		{
			i++;
			newline = 0;
		}
	}
	while (shell->cmd->argv[i])
	{
		printf("%s", shell->cmd->argv[i]);
		if (shell->cmd->argv[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
}

int builtin(t_shell *shell)
{
	char	*pwd;

	if (ft_strcmp(shell->cmd->path, "cd") == 0)
	{
		ft_cd(shell, shell->cmd->argv);
		return (1);
	}
	else if (ft_strcmp(shell->cmd->path, "pwd") == 0)
	{
		pwd = chr_path("PWD", shell->enviro);
		printf("%s\n", pwd);
		free(pwd);
		return (1);
	}
	else if (ft_strcmp(shell->cmd->path, "echo") == 0)
	{
		ft_echo(shell, 1);
		return (1);
	}
	return(0);
}
