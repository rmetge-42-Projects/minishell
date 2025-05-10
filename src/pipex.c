/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmetge <rmetge@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:18:32 by bemma             #+#    #+#             */
/*   Updated: 2025/05/10 14:33:25 by rmetge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	apply_redirections(t_list *redir_list)
{
	t_redir	*r;
	int		heredoc_fd;

	while (redir_list)
	{
		r = (t_redir *)redir_list->content;
		if (r->type == INPUT)
			open_input(r->file);
		else if (r->type == OUTPUT)
			open_out_put(r->file, 0);
		else if (r->type == APPEND)
			open_out_put(r->file, 1);
		else if (r->type == HEREDOC)
		{
			heredoc_fd = handle_heredoc(r->file);
			dup2(heredoc_fd, STDIN_FILENO);
			close(heredoc_fd);
		}
		redir_list = redir_list->next;
	}
}

static void	child_process(t_shell *shell, t_cmd *cmd, int *fd, int in_fd)
{
	apply_redirections(cmd->redirection);
	if (in_fd != 0)
		dup2(in_fd, STDIN_FILENO);
	if (cmd->pipe)
		dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	execve(cmd->path, cmd->argv, shell->env);
}

// void	ft_pipex(t_shell *shell)
// {
// 	int		fd[2];
// 	int		in_fd;
// 	pid_t	pid;
// 	t_cmd	*cmd;
// 	pid_t	pids[256];
// 	int		i = 0;
// 	int		j;

// 	in_fd = 0;
// 	cmd = shell->cmd;
// 	while (cmd)
// 	{
// 		if (pipe(fd) == -1)
// 			error("Pipe Error");
// 		pid = fork();
// 		if (pid == -1)
// 			error("Fork Error");
// 		if (pid == 0)
// 		{
// 			signal(SIGINT, SIG_IGN);
// 			child_process(shell, cmd, fd, in_fd);
// 		}
// 		pids[i++] = pid;
// 		close(fd[1]);
// 		if (in_fd != 0)
// 			close(in_fd);
// 		in_fd = fd[0];
// 		cmd = cmd->pipe;
// 	}
// 	j = 0;
// 	while (j < i)
// 	{
// 		waitpid(pids[j], NULL, 0);
// 		j++;
// 	}
// 	if (in_fd != 0)
// 		close(in_fd);
// }

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
		signal(SIGINT, SIG_IGN);
		child_process(shell, cmd, fd, in_fd);
	}
	return (pid);
}

void	ft_pipex(t_shell *shell)
{
	int		fd[2];
	int		in_fd;
	t_cmd	*cmd;
	pid_t	pids[256];
	int		i;
	int		j;

	cmd = shell->cmd;
	in_fd = 0;
	i = 0;
	while (cmd != NULL)
	{
		pids[i++] = ft_fork_child(shell, cmd, fd, in_fd);
		close(fd[1]);
		if (in_fd != 0)
			close(in_fd);
		in_fd = fd[0];
		cmd = cmd->pipe;
	}
	j = -1;
	while (++j < i)
		waitpid(pids[j], NULL, 0);
	if (in_fd != 0)
		close(in_fd);
}
