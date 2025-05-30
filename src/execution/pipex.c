/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemma <bemma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:18:32 by bemma             #+#    #+#             */
/*   Updated: 2025/05/30 13:05:26 by bemma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_last_fd(int fd, int type)
{
	dup2(fd, type);
	close(fd);
}

void	apply_redirections(t_cmd *cmd)
{
	t_redir	*r;
	t_list	*current;
	int		last_fd;

	last_fd = -1;
	current = cmd->redirection;
	while (current)
	{
		r = (t_redir *)current->content;
		if (r->type == INPUT)
			open_input(r->file);
		else if (r->type == OUTPUT)
			last_fd = open_out_put(r->file, 0);
		else if (r->type == APPEND)
			last_fd = open_out_put(r->file, 1);
		current = current->next;
	}
	if (last_fd != -1)
		ft_last_fd(last_fd, STDOUT_FILENO);
	if (cmd->last_heredoc_fd != -1)
		ft_last_fd(cmd->last_heredoc_fd, STDIN_FILENO);
}

void	put_error(t_cmd *cmd, t_shell *shell)
{
	if (cmd->path && g_sig != SIGINT)
	{
		if (!cmd->path && ft_strchr(cmd->argv[0], '/') == NULL)
		{
			ft_putstr_fd(cmd->argv[0], STDERR_FILENO);
			ft_putstr_fd(": command not found", STDERR_FILENO);
		}
		else
		{
			execve(cmd->path, cmd->argv, shell->env);
			perror(cmd->argv[0]);
		}
		shell->exit_code = 127;
		free(shell->pids);
		free_all(shell, NULL);
		free_shell(&shell);
		exit(127);
	}
}

static void	child_process(t_shell *shell, t_cmd *cmd, int *fd, int in_fd)
{
	if (in_fd != 0)
		dup2(in_fd, STDIN_FILENO);
	if (cmd->pipe && !has_output_redirection(cmd))
		dup2(fd[1], STDOUT_FILENO);
	apply_redirections(cmd);
	close(fd[0]);
	close(fd[1]);
	if (builtin(cmd) == 1)
	{
		if (ft_strcmp(cmd->path, "cd") != 0)
			apply_builtin(shell, cmd, 1);
	}
	else if (builtin(cmd) != 1)
		put_error(cmd, shell);
	free(shell->pids);
	free_all(shell, NULL);
	free_shell(&shell);
	exit(0);
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
		child_process(shell, cmd, fd, in_fd);
	return (pid);
}
