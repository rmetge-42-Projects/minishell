/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemma <bemma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:18:32 by bemma             #+#    #+#             */
/*   Updated: 2025/04/30 14:59:58 by bemma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	error(char *message)
{
	perror(message);
	exit (1);
}
void	free_struct(t_cmd *com)
{
	t_cmd	*temp;

	while (com)
	{
		temp = com->pipe;
		free(com->redirection);
		ft_free_split(com->argv);
		ft_free_split(com->path);
		com = temp;
	}
}

void	execute(char **envp, t_cmd *com)
{
	int	i;

	i = -1;
	if (!com->path)
	{
		free_split(com->argv);
		error("Path error");
	}
	if (execve(com->path, com->argv, envp) == -1)
	{
		free_struct(com);
		error("Execve Error");
	}
}
void	child_process(int *fd, t_cmd *com, char **envp)
{
	int	filein;

	filein = open(com->argv[0], O_RDONLY, 0777);
	if (filein == -1)
		error("Error fd");
	dup2(filein, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(filein);
	close(fd[1]);
	execute(envp, com->argv[1]);
}

void	parent_process(int *fd, t_cmd *com, char **envp)
{
	int	fileout;

	fileout = open(com->argv[3], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fileout == -1)
		error("Error fd");
	dup2(fd[0], STDIN_FILENO);
	dup2(fileout, STDOUT_FILENO);
	close(fd[1]);
	close(fileout);
	close(fd[0]);
	execute(envp, com->argv[2]);
}

int	ft_pipex(t_cmd *com)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;

	// if (argc != 5)
	// {
	// 	perror("Invalid argument");
	// 	return (1);
	// }
	if (pipe(fd) == -1)
		error("Pipe Error");
	pid1 = fork();
	if (pid1 == -1)
		error("Fork Error");
	else if (pid1 == 0)
		child_process(fd, com, com->path);
	waitpid(pid1, NULL, 0);
	close(fd[0]);
	pid2 = fork();
	if (pid2 == -1)
		error("Fork Error");
	else if (pid2 == 0)
		parent_process(fd, com, com->path);
	close(fd[1]);
	return (0);
}
