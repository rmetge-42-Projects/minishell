/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemma <bemma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:18:32 by bemma             #+#    #+#             */
/*   Updated: 2025/05/05 15:35:23 by bemma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	error(char *message)
{
	perror(message);
	exit (1);
}
// void	free_struct(t_cmd *comd)
// {
// 	t_cmd	*temp;

// 	while (comd)
// 	{
// 		temp = comd->pipe;
// 		free(comd->redirection);
// 		ft_f_s(&comd->com);
// 		ft_f_s(comd->path);
// 		comd = temp;
// 	}
// }

// void	execute(t_shell *mini, char *cmd)
// {
// 	int	i;

// 	i = -1;
// 	mini->cmd->path = find_path(mini, cmd);
// 	// if (!mini->cmd->path)
// 	// {
// 	// 	free_split(com->argv);
// 	// 	error("Path error");
// 	// }
// 	if (execve(mini->cmd->path, &cmd, mini->nv) == -1)
// 	{
// 		// free_struct(mini->cmd);
// 		error("Execve Error");
// 	}
// }

// void	execute(t_shell *mini)
// {
// 	int		i;

// 	i = -1;
// 	if (!mini->cmd->path)
// 	{
// 		// free_split(op);
// 		error("Path error");
// 	}
// 	if (execve(, opt, envp) == -1)
// 	{
// 		free(path);
// 		free_split(opt);
// 		error("Execve Error");
// 	}
// }

// void	child_process(int *fd, t_shell *mini)
// {
// 	int	filein;

// 	filein = open(mini->argv[0], O_RDONLY, 0777);
// 	if (filein == -1)
// 		error("Error fd");
// 	dup2(filein, STDIN_FILENO);
// 	dup2(fd[1], STDOUT_FILENO);
// 	close(fd[0]);
// 	close(filein);
// 	close(fd[1]);
// 	execute(mini, mini->argv[1]);
// }

// void	parent_process(int *fd, t_shell *mini)
// {
// 	int	fileout;

// 	fileout = open(mini->argv[3], O_WRONLY | O_CREAT | O_TRUNC, 0777);
// 	if (fileout == -1)
// 		error("Error fd");
// 	dup2(fd[0], STDIN_FILENO);
// 	dup2(fileout, STDOUT_FILENO);
// 	close(fd[1]);
// 	close(fileout);
// 	close(fd[0]);
// 	execute(mini, mini->argv[2]);
// }

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
		if(pid == 0) // qu il est dans un process
		{
			if (in_fd != 0)
				dup2(in_fd, STDIN_FILENO);// si pas la 1er commande le stdin est le meme
			if (command->pipe)
				dup2(fd[1], STDOUT_FILENO);
			close(fd[0]);
			close(fd[1]);
			execve(find_path(mini->env, command->com), command->com, mini->env);
	
		}
		close(fd[1]);
		if (in_fd != 0)
			close(in_fd);
		in_fd = fd[0];
		command = command->pipe;
	}
	// return (0);
}
