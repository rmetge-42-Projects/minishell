/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemma <bemma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:45:33 by rmetge            #+#    #+#             */
/*   Updated: 2025/06/03 14:13:32 by bemma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ctrl_c_heredoc(int fd[2], char *line)
{
	if (g_sig == SIGINT)
	{
		rl_event_hook = NULL;
		close(fd[0]);
		close(fd[1]);
		if (line)
			free(line);
		return (-1);
	}
	return (0);
}

int	heredoc_execut(int fd[2], char *delimiter, char *line, t_shell *shell)
{
	int	count_line;

	count_line = 0;
	while (1)
	{
		line = readline("> ");
		if (ctrl_c_heredoc(fd, line) == -1)
			return (-1);
		if ((!line || ft_strcmp(line, delimiter) == 0))
		{
			putstr_line(count_line, delimiter, line);
			break ;
		}
		if (ft_strchr(line, '$') && !ft_strnstr(line, "$'", ft_strlen(line))
			&& !ft_strnstr(line, "$\"", ft_strlen(line)))
			line = ft_dollar(shell, line, NULL, QUOTE2);
		ft_putendl_fd(line, fd[1]);
		count_line++;
		free(line);
	}
	return (0);
}

int	handle_heredoc(char *delimiter, t_shell *shell)
{
	int		fd[2];

	rl_event_hook = null_event;
	g_sig = 1;
	if (pipe(fd) == -1)
		error("pipe heredoc", shell);
	if (heredoc_execut(fd, delimiter, NULL, shell) == -1)
		return (-1);
	rl_event_hook = NULL;
	g_sig = 0;
	close(fd[1]);
	return (fd[0]);
}

int	ft_fd(char *str, t_shell *shell, t_cmd *tmp, int fd)
{
	char	*line;

	if (check_all_quote(str) == 0)
		line = cpy_quote(str, ft_strlen(str));
	else
		line = ft_strdup(str);
	fd = handle_heredoc(line, shell);
	if (tmp->last_heredoc_fd != -1)
		close(tmp->last_heredoc_fd);
	tmp->last_heredoc_fd = fd;
	free(line);
	return (fd);
}

int	apply_heredoc(t_shell *shell)
{
	t_redir	*r;
	t_list	*redirs;
	t_cmd	*tmp;
	int		fd;

	tmp = shell->cmd;
	fd = 0;
	while (tmp)
	{
		redirs = tmp->redirection;
		tmp->last_heredoc_fd = -1;
		while (redirs)
		{
			r = (t_redir *)redirs->content;
			if (r->type == HEREDOC)
				fd = ft_fd(r->file, shell, tmp, fd);
			redirs = redirs->next;
		}
		tmp = tmp->pipe;
	}
	return (fd);
}
