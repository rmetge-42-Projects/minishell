/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemma <bemma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:18:32 by bemma             #+#    #+#             */
/*   Updated: 2025/05/22 17:43:12 by bemma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	apply_redirections(t_cmd *cmd)
{
	t_redir	*r;
	// int		heredoc_fd;
	t_list	*current;
	// int	last_heredoc = -1;

	current = cmd->redirection;
	while (current)
	{
		dprintf(3, "current\n");
		r = (t_redir *)cmd->redirection->content;
		if (r->type == INPUT)
			open_input(r->file);
		else if (r->type == OUTPUT)
			open_out_put(r->file, 0);
		else if (r->type == APPEND)
			open_out_put(r->file, 1);
		// else if (r->type == HEREDOC)
		// {
		// 	// // signal(SIGINT, ft_ctrl_c);
		// 	// signal(SIGQUIT, SIG_IGN);
		// 	// heredoc_fd = handle_heredoc(r->file);
		// 	// //dprintf(3, "finisssshhshshshshsh");
			
		// 	// signal(SIGQUIT, SIG_IGN);
		// 	// continue ;
			
		// }
		current = current->next;
	}
	if (cmd->last_heredoc_fd != -1)
	{
		dprintf(3, "HEREDOC A DUP; %d\n", cmd->last_heredoc_fd);
		dup2(cmd->last_heredoc_fd, STDIN_FILENO);
		close(cmd->last_heredoc_fd);
	}
}

static void	child_process(t_shell *shell, t_cmd *cmd, int *fd, int in_fd)
{
	apply_redirections(cmd);
	// dprintf(3,"vraiment con");
	// signal(SIGQUIT, ft_ctrl_backslash);
	// signal(SIGINT, SIG_DFL);
	
	if (in_fd != 0)
		dup2(in_fd, STDIN_FILENO);
	if (cmd->pipe)
		dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	if (cmd->path && g_sig != SIGINT)
	{
		// signal(SIGQUIT, ft_ctrl_backslash);
		g_sig = 0;
		manege_signal();
		execve(cmd->path, cmd->argv, shell->env);
		// signal(SIGQUIT, ft_ctrl_backslash);
	}
	// dprintf(3 ,"GROS TEST");
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
	// g_sig = 0;
	// // test();
	// manege_signal();
	pid = fork();
	if (pid == -1)
		error("Fork Error");
	if (pid == 0)
	{
		child_process(shell, cmd, fd, in_fd);
	}
	// manege_signal();
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
	t_cmd	*tmp;
	int		cmd_count;
	t_redir *r;
	t_list	*redirs;
	int		i;
	int		fd_here_temp;

	
	
	in_fd = 0;
	i = 0;
	cmd_count = count_cmds(shell->cmd);
	shell->pids = malloc(sizeof(pid_t) * cmd_count);
	tmp = shell->cmd;
	// manege_signal();
	// rl_catch_signals = 0;
	while (tmp)
	{
		redirs = tmp->redirection;
		tmp->last_heredoc_fd = -1;
		while (redirs)
		{
			r = (t_redir *)redirs->content;
			if (r->type == HEREDOC)
			{
				fd_here_temp = handle_heredoc(r->file);
				// dprintf(3, "HEREDOC TEMP; %d\n", fd_here_temp);
				if (tmp->last_heredoc_fd != -1)
					close(tmp->last_heredoc_fd);
				tmp->last_heredoc_fd = fd_here_temp;
				// close(fd_here_temp);
				// dprintf(3, "HEREDOC STRUCT; %d\n", tmp->last_heredoc_fd);
			}
			redirs = redirs->next;
		}
		
		tmp = tmp->pipe;
	}
	
	cmd = shell->cmd;
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
	if (fd_here_temp != -1)
		close(fd_here_temp);
	free(shell->pids);
}
