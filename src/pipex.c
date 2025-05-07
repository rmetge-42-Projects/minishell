/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemma <bemma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:18:32 by bemma             #+#    #+#             */
/*   Updated: 2025/05/07 14:56:11 by bemma            ###   ########.fr       */
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
void	redirect_in_out(t_redir *r, int fd)
{
	if (r->type == INPUT)
	{
		fd = open(r->file, O_RDONLY);
		if (fd == -1)
			error("infile");
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (r->type == OUTPUT)
	{
		fd = open(r->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			error("outfile");
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else if (r->type == APPEND)
	{
		fd = open(r->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			error("outfile append");
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}

void	apply_redirections(t_list *redir_list)
{
	t_redir	*r;
	int		fd;
	int		heredoc_fd;

	fd = 0;
	while (redir_list)
	{
		r = (t_redir *)redir_list->content;
		redirect_in_out(r, fd);
		if (r->type == HEREDOC)
		{
			heredoc_fd = handle_heredoc(r->file);
			dup2(heredoc_fd, STDIN_FILENO);
			close(heredoc_fd);
		}
		redir_list = redir_list->next;
	}
}
void	execution(t_shell *shell, int in_fd, int *fd, t_cmd *command)
{
	if (in_fd != 0)
		dup2(in_fd, STDIN_FILENO);
	if (command->pipe)
		dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	apply_redirections(command->redirection);
	execve(find_path(shell->env, *command->argv), command->argv, shell->env);
}

void	ft_pipex(t_shell *shell)
{
	int		fd[2];
	int		in_fd;
	int		status;
	pid_t	pid;
	t_cmd	*command;

	command = shell->cmd;
	in_fd = 0;
	while (command)
	{
		if (pipe(fd) == -1)
			error("Pipe Error");
		pid = fork();
		if (pid == -1)
			error("Fork Error");
		if(pid == 0)
			execution(shell, in_fd, &fd[2], command);
		else if (pid > 0)
			waitpid(pid, &status, 0);
		close(fd[1]);
		if (in_fd != 0)
			close(in_fd);
		in_fd = fd[0];
		command = command->pipe;
	}
}
