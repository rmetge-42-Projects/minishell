/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmetge <rmetge@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:57:05 by bemma             #+#    #+#             */
/*   Updated: 2025/05/23 16:32:10 by rmetge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error(char *message)
{
	perror(message);
	exit (1);
}

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

int null_event(){
	return (1);
	}

int	handle_heredoc(char *delimiter)
{
	int		fd[2];
	char	*line;
	int		count_line;

	rl_event_hook = null_event;
	g_sig = 1;
	count_line = 0;
	if (pipe(fd) == -1)
		error("pipe heredoc");
	while (1)
	{
		line = readline("> ");
		if (g_sig == SIGINT)
		{
			rl_event_hook = NULL;
			close(fd[0]);
			close(fd[1]);
			if (line)
				free(line);
			return (-1);
		}
		else if ((!line || ft_strcmp(line, delimiter) == 0))
		{

			if (!line)
			{
				ft_putstr_fd("bash: warning: here-document at line ", 2);
				ft_putnbr_fd(count_line, 2);
				ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
				ft_putstr_fd(delimiter, 2);
				ft_putstr_fd("')\n", 2);
			}
			break ;
		}
		else
		{
			ft_putendl_fd(line, fd[1]);
			count_line++;
			free(line);
		}
	}
	rl_event_hook = NULL;
	g_sig = 0;
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
