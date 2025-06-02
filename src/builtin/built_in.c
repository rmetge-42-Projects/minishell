/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemma <bemma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:17:53 by bemma             #+#    #+#             */
/*   Updated: 2025/06/02 15:55:06 by bemma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	apply_builtin(t_shell *shell, t_cmd *cmd, int pipe)
{
	int	fd;
	int	ex_code;

	fd = 1;
	ex_code = 1;
	if (pipe == 0)
		fd = redirection_bulitin(cmd, shell);
	if (ft_strcmp(cmd->path, "cd") == 0)
		ex_code = ft_cd(shell, cmd->argv);
	else if (ft_strcmp(cmd->path, "pwd") == 0)
		ex_code = ft_pwd(fd);
	else if (ft_strcmp(cmd->path, "echo") == 0)
		ex_code = ft_echo(cmd, 1, fd, shell);
	else if (ft_strcmp(cmd->path, "unset") == 0)
		ex_code = ft_unset(shell, shell->cmd);
	else if (ft_strcmp(cmd->path, "export") == 0)
		ex_code = ft_export(shell, shell->cmd);
	else if (ft_strcmp(cmd->path, "env") == 0)
		ex_code = ft_env(shell);
	else if (ft_strcmp(cmd->path, "exit") == 0)
		ex_code = ft_exit(shell, cmd);
	shell->exit_code = ex_code;
}

int	builtin(t_cmd *cmd)
{
	if (!cmd->path)
		return (0);
	if (ft_strcmp(cmd->path, "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd->path, "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd->path, "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd->path, "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd->path, "export") == 0)
		return (1);
	if (ft_strcmp(cmd->path, "env") == 0)
		return (1);
	else if (ft_strcmp(cmd->path, "exit") == 0)
		return (1);
	return (0);
}
