/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmetge <rmetge@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:18:32 by bemma             #+#    #+#             */
/*   Updated: 2025/05/27 13:21:03 by rmetge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			last_fd = open_out_put(r->file, 0, last_fd);
		else if (r->type == APPEND)
			last_fd = open_out_put(r->file, 1, last_fd);
		current = current->next;
	}
	if (last_fd != -1)
	{
		dup2(last_fd, STDOUT_FILENO);
		close(last_fd);
	}
	if (cmd->last_heredoc_fd != -1)
	{
		dup2(cmd->last_heredoc_fd, STDIN_FILENO);
		close(cmd->last_heredoc_fd);
	}
}


static void	child_process(t_shell *shell, t_cmd *cmd, int *fd, int in_fd)
{
	if (in_fd != 0)
		dup2(in_fd, STDIN_FILENO);
	apply_redirections(cmd);

	if (cmd->pipe && !has_output_redirection(cmd))
		dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	if (builtin(cmd) == 1)
	{
		if (ft_strcmp(cmd->path, "cd") != 0)
			apply_builtin(shell, cmd, 1);
	}
	else if (builtin(cmd) != 1)
	{
		if (cmd->path && g_sig != SIGINT)
		{
			if (execve(cmd->path, cmd->argv, shell->env) == -1)
				printf("eurreur\n");
			// execve(cmd->path, cmd->argv, shell->env);
			// printf("erreur\n");
		}
	}
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
		child_process(shell, cmd, fd, in_fd);
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

int apply_heredoc(t_shell *shell)
{
	t_redir	*r;
	t_list	*redirs;
	t_cmd	*tmp;
	int		fd;

	tmp = shell->cmd;
	while (tmp)
	{
		redirs = tmp->redirection;
		tmp->last_heredoc_fd = -1;
		while (redirs)
		{
			r = (t_redir *)redirs->content;
			if (r->type == HEREDOC)
			{
				fd = handle_heredoc(r->file);
				if (tmp->last_heredoc_fd != -1)
					close(tmp->last_heredoc_fd);
				tmp->last_heredoc_fd = fd;
			}
			redirs = redirs->next;
		}
		tmp = tmp->pipe;
	}
	return (fd);
}
