/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemma <bemma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:18:32 by bemma             #+#    #+#             */
/*   Updated: 2025/05/06 15:48:11 by bemma            ###   ########.fr       */
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
	close(fd[1]); // on ferme l'entrée, pour signaler EOF
	return (fd[0]); // on retourne la sortie du pipe à rediriger vers STDIN
}


void	apply_redirections(t_list *redir_list)
{
	t_redir	*r;
	int		fd;
	int		heredoc_fd;

	while (redir_list)
	{
		r = (t_redir *)redir_list->content;
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
		else if (r->type == HEREDOC)
		{
			heredoc_fd = handle_heredoc(r->file);
			dup2(heredoc_fd, STDIN_FILENO);
			close(heredoc_fd);
		}

		// HEREDOC sera traité à part (buffer temporaire ou pipe)
		redir_list = redir_list->next;
	}
}


void	ft_pipex(t_shell *mini)
{
	int		fd[2];
	int		in_fd = 0;
	pid_t	pid;
	t_cmd	*command = mini->cmd;

	while (command)
	{
		if (pipe(fd) == -1)
			error("Pipe Error");

		pid = fork();
		if (pid == -1)
			error("Fork Error");

		if(pid == 0) // qu il est dans un process
		{
			if (in_fd != 0)
				dup2(in_fd, STDIN_FILENO);//Rediriger STDIN s’il y a une commande précédente,Si ce n’est pas la première commande, on lit à partir du pipe précédent.
			if (command->pipe)
				dup2(fd[1], STDOUT_FILENO);//Rediriger STDOUT si une commande suivante existe, Si ce n’est pas la dernière commande, on écrit dans le pipe courant pour passer la sortie à la suivante
			close(fd[0]);//Fermeture des descripteurs inutiles
			close(fd[1]);//
			apply_redirections(command->redirection);// gere < > <<
			execve(find_path(mini->env, *command->com), command->com, mini->env);
	
		}
		close(fd[1]);
		if (in_fd != 0)
			close(in_fd);
		in_fd = fd[0];
		command = command->pipe;
	}
	// return (0);
}
