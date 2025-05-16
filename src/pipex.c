/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemma <bemma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:18:32 by bemma             #+#    #+#             */
/*   Updated: 2025/05/16 15:06:03 by bemma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	apply_redirections(t_cmd *cmd)
{
	t_redir	*r;
	int		heredoc_fd;
	t_list *current;

	current = cmd->redirection;
	while (current)
	{
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
			if (cmd->path)
				dup2(heredoc_fd, STDIN_FILENO);
			close(heredoc_fd);
		}
		current = current->next;
	}
}

static void	child_process(t_shell *shell, t_cmd *cmd, int *fd, int in_fd)
{
	apply_redirections(cmd);
	close(fd[0]);
	close(fd[1]);
	if (cmd->path)
	{
		if (in_fd != 0)
			dup2(in_fd, STDIN_FILENO);
		if (cmd->pipe)
			dup2(fd[1], STDOUT_FILENO);
		execve(cmd->path, cmd->argv, shell->env);
		
	}
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
		
		manege_signal();
		child_process(shell, cmd, fd, in_fd);
	}
	return (pid);
}

int	count_cmds(t_cmd *cmd)
{
	int count = 0;

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
	pid_t	*pids;
	int		cmd_count = count_cmds(shell->cmd);
	int		i;

	cmd = shell->cmd;
	in_fd = 0;
	i = 0;
	pids = malloc(sizeof(pid_t) * cmd_count);
	while (cmd != NULL)
	{
		pids[i++] = ft_fork_child(shell, cmd, fd, in_fd);
		close(fd[1]);
		if (in_fd != 0)
			close(in_fd);
		in_fd = fd[0];
		cmd = cmd->pipe;
	}
	ft_wait(cmd_count, pids);
	if (in_fd != 0)
		close(in_fd);
	free(pids);
}
