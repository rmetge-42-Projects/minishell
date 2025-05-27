/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmetge <rmetge@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 11:26:11 by rmetge            #+#    #+#             */
/*   Updated: 2025/05/27 14:34:04 by rmetge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pipex_before(t_shell *shell)
{
	int		fd_here_temp;

	if (!shell->cmd->pipe && builtin(shell->cmd) == 1)
	{
		apply_builtin(shell, shell->cmd, 0);
		return (1);
	}
	fd_here_temp = apply_heredoc(shell);
	return (0);
}

void close_free(int in_fd, t_shell *shell)
{
	if (in_fd != 0)
		close(in_fd);
	if (shell->cmd->last_heredoc_fd != -1)
		close(shell->cmd->last_heredoc_fd);
	free(shell->pids);
}

void	ft_pipex(t_shell *shell)
{
	int		fd[2];
	int		in_fd;
	t_cmd	*cmd;
	int		cmd_count;
	int		i;

	if (ft_pipex_before(shell) == 1)
		return ;
	in_fd = 0;
	i = 0;
	cmd_count = count_cmds(shell->cmd);
	shell->pids = malloc(sizeof(pid_t) * cmd_count);
	cmd = shell->cmd;
	while (cmd != NULL)
	{
		shell->pids[i++] = ft_fork_child(shell, cmd, fd, in_fd);
		close(fd[1]);
		if (in_fd != 0)
			close(in_fd);
		if (!has_output_redirection(cmd))
			in_fd = fd[0];
		else
			in_fd = 0;
		g_sig = 0;
		cmd = cmd->pipe;
	}
	ft_wait(cmd_count, shell->pids);
	close_free(in_fd, shell);
}
