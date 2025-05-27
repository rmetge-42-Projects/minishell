/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmetge <rmetge@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:17:53 by bemma             #+#    #+#             */
/*   Updated: 2025/05/27 11:15:46 by rmetge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char *ft_strndup(const char *s, size_t n)
// {
// 	char	*dup;
// 	size_t	len;

// 	if (!s)
// 		return (NULL);
// 	len = strnlen(s, n); // Trouve la longueur réelle à copier (max n)
// 	dup = malloc(len + 1); // Alloue la mémoire pour la nouvelle chaîne
// 	if (!dup)
// 		return (NULL);
// 	ft_memcpy(dup, s, len); // Copie les caractères
// 	dup[len] = '\0'; // Ajoute le caractère nul de fin
// 	return (dup);
// }

// void	ft_ctrl_c(int sig)
// {
// 	(void)sig;

// 	write(1, "\n", 1);
// 	rl_on_new_line();
// 	rl_replace_line("", 0);
// 	rl_redisplay();
// }

int	ft_exit(t_shell *shell)
{
	char	**args;

	args = ft_split(shell->line, ' ');
	if (ft_strncmp(args[0], "exit", 5) == 0)
		return (ft_free_split(args), 1);
	return (ft_free_split(args), 0);
}

void	apply_builtin(t_shell *shell, t_cmd *cmd, int pipe)
{
	int		fd;

	fd = 1;
	if (pipe == 0)
		fd = redirection_bulitin(cmd);
	// if (!fd)
	if (ft_strcmp(cmd->path, "cd") == 0)
		ft_cd(shell, cmd->argv);
	else if (ft_strcmp(cmd->path, "pwd") == 0)
		ft_pwd(fd);
	else if (ft_strcmp(cmd->path, "echo") == 0)
		ft_echo(cmd, 1, fd);
	else if (ft_strcmp(cmd->path, "unset") == 0)
		ft_unset(shell, shell->cmd);
	else if (ft_strcmp(cmd->path, "export") == 0)
		ft_export(shell);
	else if (ft_strncmp(cmd->path, "env", 4) == 0)
		ft_env(shell);
}

int	builtin(t_cmd *cmd)
{
	// (void)shell;
	if (!cmd->path)
		return (0);
	if (ft_strcmp(cmd->path, "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd->path, "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd->path, "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd->path, "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd->path, "export") == 0)
		return (1);
	if (ft_strcmp(cmd->path, "env") == 0)
		return (1);
	return (0);
}


// int	bultin(t_shell *shell)
// {
// 	t_env	*current;

// 	// if (ft_strncmp(shell->args[0], "export", 7) == 0)
// 	// {
// 	// 	ft_export(shell);
// 	// 	return (1);
// 	// }
// 	if (ft_strncmp(shell->args[0], "env", 4) == 0
// 		|| ft_strncmp(shell->args[0], "envp", 5) == 0)
// 	{
// 		current = shell->enviro;
// 		while (current)
// 		{
// 			if (current->value)
// 				printf("%s=%s\n", current->key, current->value);
// 			current = current->next;
// 		}
// 		return (1);
// 	}
// 	return (0);
// }
