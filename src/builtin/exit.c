/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemma <bemma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 10:56:40 by bemma             #+#    #+#             */
/*   Updated: 2025/05/28 14:25:31 by bemma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if(str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

void	exit_shell(t_shell *shell, int exit_code, int i)
{
	if (i == 1)
		free_all(shell, shell->line);
	free_shell(&shell);
	exit(exit_code);
}

int	ft_exit(t_shell *shell, t_cmd *cmd)
{
	int	exit_code;
	char	**args;

	args = cmd->argv;
	if (shell->tty)
		ft_putendl_fd("exit", STDERR_FILENO);
	if (!args[1])
		exit_shell(shell, shell->exit_code, 1);
	if (is_numeric(args[1]) == 0)
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putstr_fd("numeric argument required", STDERR_FILENO);
		exit_shell(shell, 2, 1);
	}
	if (args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		shell->exit_code = 1;
		return (1);
	}
	exit_code = ft_atoi(args[1]);
	exit_shell(shell, exit_code, 1);
	return (0);
}