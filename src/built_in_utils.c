/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmetge <rmetge@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 09:14:50 by rmetge            #+#    #+#             */
/*   Updated: 2025/05/23 18:03:17 by rmetge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_shell *shell, int newline, int fd)
{
	int	i;
	int	j;

	i = 1;
	while (shell->cmd->argv[i] != NULL
		&& ft_strncmp(shell->cmd->argv[i], "-n", 2) == 0)
	{
		j = 2;
		while (shell->cmd->argv[i][j] == 'n')
			j++;
		if (!shell->cmd->argv[i][j])
		{
			i++;
			newline = 0;
		}
	}
	while (shell->cmd->argv[i])
	{
		ft_putstr_fd(shell->cmd->argv[i], fd);
		// printf("%s", shell->cmd->argv[i]);
		if (shell->cmd->argv[i + 1] != NULL)
			// printf(" ");
			ft_putstr_fd(" ", fd);
		i++;
	}
	if (newline)
		ft_putstr_fd("\n", fd);
}

void	ft_unset(t_shell *shell)
{
	t_env	*env;
	t_env	*tmp;
	int		i;

	env = shell->enviro;
	i = 1;
	if (!shell->cmd->argv[1])
		return ;
	while (shell->cmd->argv[i])
	{
		while (env->next && ft_strcmp(env->next->key, shell->cmd->argv[i]) != 0)
			env = env->next;
		if (env->next && ft_strcmp(env->next->key, shell->cmd->argv[i]) == 0)
		{
			tmp = env->next;
			// free(env->next);
			env->next = env->next->next;
			free(tmp->key);
			free(tmp->value);
			free(tmp);
			// env->next->value = ft_strdup("(null)");
		}
		i++;
	}
}

void	ft_pwd(int fd)
{
	char	pwd[1024];

	getcwd(pwd, sizeof(pwd));
	ft_putstr_fd(pwd, fd);
	ft_putstr_fd("\n", fd);
}

void	apply_builtin(t_shell *shell)
{
	int		fd;

	fd = redirection_bulitin(shell->cmd);
	if (ft_strcmp(shell->cmd->path, "cd") == 0)
	{
		ft_cd(shell, shell->cmd->argv);
	}
	else if (ft_strcmp(shell->cmd->path, "pwd") == 0)
		ft_pwd(fd);
	else if (ft_strcmp(shell->cmd->path, "echo") == 0)
	{
		ft_echo(shell, 1, fd);
	}
	else if (ft_strcmp(shell->cmd->path, "unset") == 0)
	{
		ft_unset(shell);
	}
	else if (ft_strcmp(shell->cmd->path, "export") == 0)
	{
		ft_export(shell);
	}
	// close (fd);
}

int	builtin(t_shell *shell)
{
	// (void)shell;
	if (!shell->cmd->path)
		return (0);
	if (ft_strcmp(shell->cmd->path, "cd") == 0)
		return (1);
	else if (ft_strcmp(shell->cmd->path, "pwd") == 0)
		return (1);
	else if (ft_strcmp(shell->cmd->path, "echo") == 0)
		return (1);
	else if (ft_strcmp(shell->cmd->path, "unset") == 0)
		return (1);
	else if (ft_strcmp(shell->cmd->path, "export") == 0)
		return (1);
	return (0);
}
