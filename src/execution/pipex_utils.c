/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemma <bemma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:57:05 by bemma             #+#    #+#             */
/*   Updated: 2025/05/28 11:39:29 by bemma            ###   ########.fr       */
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
	int	i;

	i = 0;
	while (i < count)
	{
		waitpid(pids[i], NULL, 0);
		i++;
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
		// if (isatty(STDIN_FILENO))
			line = readline("> ");
		// else
			//line = readline(NULL);
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

			if (!line && isatty(STDIN_FILENO))
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

int	has_input_redirection(t_cmd *cmd)
{
	t_list	*current = cmd->redirection;
	t_redir	*r;

	while (current)
	{
		r = (t_redir *)current->content;
		if (r->type == INPUT || r->type == HEREDOC)
			return (1);
		current = current->next;
	}
	return (0);
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