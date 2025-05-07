/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemma <bemma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:18:32 by bemma             #+#    #+#             */
/*   Updated: 2025/05/07 16:31:08 by bemma            ###   ########.fr       */
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
			break;
		write(fd[1], line, strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
	free(line);
	close(fd[1]);
	return (fd[0]);
}


// void	apply_redirections(t_list *redir_list)
// {
// 	t_redir	*r;
// 	int		fd;
// 	int		heredoc_fd;

// 	while (redir_list)
// 	{
// 		r = (t_redir *)redir_list->content;
// 		if (r->type == INPUT)
// 		{
// 			fd = open(r->file, O_RDONLY);
// 			if (fd == -1)
// 				error("infile");
// 			dup2(fd, STDIN_FILENO);
// 			close(fd);
// 		}
// 		else if (r->type == OUTPUT)
// 		{
// 			fd = open(r->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 			if (fd == -1)
// 				error("outfile");
// 			dup2(fd, STDOUT_FILENO);
// 			close(fd);
// 		}
// 		else if (r->type == APPEND)
// 		{
// 			fd = open(r->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
// 			if (fd == -1)
// 				error("outfile append");
// 			dup2(fd, STDOUT_FILENO);
// 			close(fd);
// 		}
// 		else if (r->type == HEREDOC)
// 		{
// 			heredoc_fd = handle_heredoc(r->file);
// 			dup2(heredoc_fd, STDIN_FILENO);
// 			close(heredoc_fd);
// 		}
// 		redir_list = redir_list->next;
// 	}
// }

static void	open_input(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		error("infile");
	dup2(fd, STDIN_FILENO);
	close(fd);
}

static void	open_output(char *file, int append)
{
	int	fd;
	int	flags;

	flags = O_WRONLY | O_CREAT | (append ? O_APPEND : O_TRUNC);
	fd = open(file, flags, 0644);
	if (fd == -1)
		error(append ? "outfile append" : "outfile");
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
	if (in_fd != 0)
		dup2(in_fd, STDIN_FILENO);
	if (cmd->pipe)
		dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	apply_redirections(cmd->redirection);
	execve(find_path(shell->env, *cmd->argv), cmd->argv, shell->env);
}

void	ft_pipex(t_shell *shell)
{
	int		fd[2];
	int		in_fd;
	pid_t	pid;
	t_cmd	*cmd;
	int		status;

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
		waitpid(pid, &status, 0);
		close(fd[1]);
		if (in_fd != 0)
			close(in_fd);
		in_fd = fd[0];
		cmd = cmd->pipe;
	}
}


// void	ft_pipex(t_shell *shell)
// {
// 	int		fd[2];
// 	int		in_fd = 0;
// 	pid_t	pid;
// 	t_cmd	*command = shell->cmd;


// 	while (command)
// 	{
// 		if (pipe(fd) == -1)
// 			error("Pipe Error");

// 		pid = fork();
// 		if (pid == -1)
// 			error("Fork Error");

// 		if(pid == 0)
// 		{
// 			if (in_fd != 0)
// 				dup2(in_fd, STDIN_FILENO);
// 			if (command->pipe)
// 				dup2(fd[1], STDOUT_FILENO);
// 			close(fd[0]);
// 			close(fd[1]);
// 			apply_redirections(command->redirection);
// 			execve(find_path(shell->env, *command->argv), command->argv, shell->env);
// 		}
// 		else if (pid > 0)
// 		{
// 			int status;
// 			waitpid(pid, &status, 0);
// 		}
// 		close(fd[1]);
// 		if (in_fd != 0)
// 			close(in_fd);
// 		in_fd = fd[0];
// 		command = command->pipe;
// 	}
// }
