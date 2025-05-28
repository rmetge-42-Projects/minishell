/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemma <bemma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:18:32 by bemma             #+#    #+#             */
/*   Updated: 2025/05/28 15:34:11 by bemma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_last_fd(int fd)
{
	dup2(fd, STDOUT_FILENO);
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
			last_fd = open_out_put(r->file, 0, last_fd);
		else if (r->type == APPEND)
			last_fd = open_out_put(r->file, 1, last_fd);
		current = current->next;
	}
	if (last_fd != -1)
		ft_last_fd(last_fd);
	if (cmd->last_heredoc_fd != -1)
		ft_last_fd(cmd->last_heredoc_fd);
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
	{
		if (cmd->path && g_sig != SIGINT)
		{
			if (ft_strchr(cmd->argv[0], '/'))
			{
				// cas d’un chemin absolu ou relatif
				execve(cmd->path, cmd->argv, shell->env);
				perror(cmd->argv[0]); // affiche "No such file or directory" ou autre
				shell->exit_code = 127;
				free(shell->pids);
				free_all(shell, NULL);
				free_shell(&shell);
				exit(127);
			}
			else
			{
				if (!cmd->path)
				{
					ft_putstr_fd(cmd->argv[0], STDERR_FILENO);
					ft_putstr_fd(": command not found", STDERR_FILENO);
					shell->exit_code = 127;
					free(shell->pids);
					free_all(shell, NULL);
					free_shell(&shell);
					exit(127);
				}
				execve(cmd->path, cmd->argv, shell->env);
				perror(cmd->argv[0]);
				shell->exit_code = 127;
				free(shell->pids);
				free_all(shell, NULL);
				free_shell(&shell);
				exit(127);
			}
				// printf("eurreur\n");
			// execve(cmd->path, cmd->argv, shell->env);
			// printf("erreur\n");
		}
	}
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
