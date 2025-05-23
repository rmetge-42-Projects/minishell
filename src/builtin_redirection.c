/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmetge <rmetge@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:45:53 by rmetge            #+#    #+#             */
/*   Updated: 2025/05/23 17:17:50 by rmetge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_input(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		error("infile");
	return (fd);
}

int	builtin_out_put(char *file, int append)
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
	return (fd);
}

int	redirection_bulitin(t_cmd *cmd)
{
	t_redir	*r;
	t_list	*current;
	int		fd;

	current = cmd->redirection;
	fd = 1;
	while (current)
	{
		r = (t_redir *)cmd->redirection->content;
		if (r->type == INPUT)
			builtin_input(r->file);
		else if (r->type == OUTPUT)
			fd = builtin_out_put(r->file, 0);
		else if (r->type == APPEND)
			fd = builtin_out_put(r->file, 1);
		current = current->next;
	}
	// if (cmd->last_heredoc_fd != -1)
	// {
	// 	dup2(cmd->last_heredoc_fd, STDIN_FILENO);
	// 	close(cmd->last_heredoc_fd);
	// }
	return (fd);
}