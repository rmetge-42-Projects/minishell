/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmetge <rmetge@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:57:05 by bemma             #+#    #+#             */
/*   Updated: 2025/05/27 15:42:24 by rmetge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_wait(int count, pid_t *pids)
{
	int	j;

	j = 0;
	while (j < count)
	{
		waitpid(pids[j], NULL, 0);
		j++;
	}
}

void	open_input(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		error("infile");
	dup2(fd, STDIN_FILENO);
	close(fd);
}

int	open_out_put(char *file, int append, int last_fd)
{
	int	fd;

	if (append == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		if (append == 1)
			error("outfile append");
		else
			error("outfile");
	}
	if (last_fd != -1)
	{
		dup2(last_fd, STDOUT_FILENO);
		close(last_fd);
	}
	return (fd);
}

int	has_output_redirection(t_cmd *cmd)
{
	t_list	*current;
	t_redir	*r;

	current = cmd->redirection;
	while (current)
	{
		r = (t_redir *)current->content;
		if (r->type == OUTPUT || r->type == APPEND)
			return (1);
		current = current->next;
	}
	return (0);
}

void	error(char *message)
{
	perror(message);
	exit (1);
}
