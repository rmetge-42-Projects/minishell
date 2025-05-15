/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemma <bemma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:57:05 by bemma             #+#    #+#             */
/*   Updated: 2025/05/15 16:41:28 by bemma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error(char *message)
{
	perror(message);
	exit (1);
}

void	ft_wait(int i, pid_t pids[256])
{
	int	j;

	j = -1;
	while (++j < i)
		waitpid(pids[j], NULL, 0);
}

int	handle_heredoc(char *delimiter)
{
	int		fd[2];
	char	*line;

	g_sig = 1;
	rl_event_hook = check_ctrl_c_h;
	if (pipe(fd) == -1)
		error("pipe heredoc");
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			rl_event_hook = NULL;
			g_sig = 0;
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd[1]);
		ft_putstr_fd("\n", fd[1]);
		free(line);
	}
	close(fd[1]);
	return (fd[0]);
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

void	open_out_put(char *file, int append)
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
	dup2(fd, STDOUT_FILENO);
	close(fd);
}
