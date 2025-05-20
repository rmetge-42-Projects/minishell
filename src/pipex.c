/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemma <bemma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:18:32 by bemma             #+#    #+#             */
/*   Updated: 2025/05/20 16:29:05 by bemma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	apply_redirections(t_cmd *cmd)
{
	t_redir	*r;
	int		heredoc_fd;
	t_list	*current;

	current = cmd->redirection;
	while (current)
	{
		//dprintf(3, "current");
		r = (t_redir *)cmd->redirection->content;
		if (r->type == INPUT)
			open_input(r->file);
		else if (r->type == OUTPUT)
			open_out_put(r->file, 0);
		else if (r->type == APPEND)
			open_out_put(r->file, 1);
		else if (r->type == HEREDOC)
		{
			heredoc_fd = handle_heredoc(r->file);
			dprintf(3, "finisssshhshshshshsh");
			if (heredoc_fd != -1 && cmd->path)
			{
				dup2(heredoc_fd, STDIN_FILENO);
				close(heredoc_fd);
			}
		}
		current = current->next;
	}
}

static void	child_process(t_shell *shell, t_cmd *cmd, int *fd, int in_fd)
{
	apply_redirections(cmd);
	dprintf(3,"vraiment con");
	if (in_fd != 0)
		dup2(in_fd, STDIN_FILENO);
	if (cmd->pipe)
		dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	if (cmd->path)
		execve(cmd->path, cmd->argv, shell->env);
	free(shell->pids);
	free_all(shell, NULL);
	free_shell(&shell);
	exit(1);
}

pid_t	ft_fork_child(t_shell *shell, t_cmd *cmd, int *fd, int in_fd)
{
	pid_t	pid;

	if (pipe(fd) == -1)
		error("Pipe Error");
	pid = fork();
	if (pid == -1)
		error("Fork Error");
	if (pid == 0)
	{
		g_sig = 1;
		manege_signal();
		child_process(shell, cmd, fd, in_fd);
	}
	return (pid);
}

int	count_cmds(t_cmd *cmd)
{
	int	count;

	count = 0;
	while (cmd != NULL)
	{
		count++;
		cmd = cmd->pipe;
	}
	return (count);
}

void	ft_pipex(t_shell *shell)
{
	int		fd[2];
	int		in_fd;
	t_cmd	*cmd;
	int		cmd_count;
	int		i;

	cmd = shell->cmd;
	in_fd = 0;
	i = 0;
	cmd_count = count_cmds(shell->cmd);
	shell->pids = malloc(sizeof(pid_t) * cmd_count);
	while (cmd != NULL)
	{
		shell->pids[i++] = ft_fork_child(shell, cmd, fd, in_fd);
		close(fd[1]);
		if (in_fd != 0)
			close(in_fd);
		in_fd = fd[0];
		cmd = cmd->pipe;
	}
	ft_wait(cmd_count, shell->pids);
	if (in_fd != 0)
		close(in_fd);
	free(shell->pids);
}
