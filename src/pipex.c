/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmetge <rmetge@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:18:32 by bemma             #+#    #+#             */
/*   Updated: 2025/05/10 14:24:12 by rmetge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	error(char *message)
{
	perror(message);
	exit (1);
}

int	handle_heredoc(char *delimiter)
{
	int		fd[2];
	char	*line;

	if (pipe(fd) == -1)
		error("pipe heredoc");

	while (1)
	{
		line = readline("> ");
		if (!line || strcmp(line, delimiter) == 0)
		{
			free(line);
			break;
		}
		write(fd[1], line, strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
	close(fd[1]);
	return (fd[0]);
}

static void	open_input(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		error("infile");
	dup2(fd, STDIN_FILENO);
	close(fd);
}

// static void	open_output(char *file, int append)
// {
// 	int	fd;
// 	int	flags;

// 	flags = O_WRONLY | O_CREAT | (append ? O_APPEND : O_TRUNC);
// 	fd = open(file, flags, 0644);
// 	if (fd == -1)
// 		error(append ? "outfile append" : "outfile");
// 	dup2(fd, STDOUT_FILENO);
// 	close(fd);
// }

static void	open_output(char *file, int append)
{
	int	fd;
	int	flags;

	flags = O_WRONLY | O_CREAT;
	if (append == 1)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;

	fd = open(file, flags, 0644);
	if (fd == -1)
	{
		if (append == 1)
			error("outfile append");
		else
			error("outfile");
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

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
			open_output(r->file, 0);
		else if (r->type == APPEND)
			open_output(r->file, 1);
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

void	ft_pipex(t_shell *shell)
{
	int		fd[2];
	int		in_fd;
	pid_t	pid;
	t_cmd	*cmd;
	pid_t	pids[256];
	int		i = 0;

	in_fd = 0;
	cmd = shell->cmd;
	while (cmd)
	{
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
		pids[i++] = pid;
		close(fd[1]);
		if (in_fd != 0)
			close(in_fd);
		in_fd = fd[0];
		cmd = cmd->pipe;
	}
	int j = 0;
	while (j < i)
	{
		waitpid(pids[j], NULL, 0);
		j++;
	}
	if (in_fd != 0)
		close(in_fd);
}
