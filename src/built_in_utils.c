/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmetge <rmetge@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 09:14:50 by rmetge            #+#    #+#             */
/*   Updated: 2025/05/26 20:04:52 by rmetge           ###   ########.fr       */
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
		if (shell->cmd->argv[i][j])
			break;
		i++;
		newline = 0;
	}
	while (shell->cmd->argv[i])
	{
		ft_putstr_fd(shell->cmd->argv[i], fd);
		if (shell->cmd->argv[i + 1] != NULL)
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

int	ft_pwd(int fd)
{
	char	pwd[1024];

	if (getcwd(pwd, sizeof(pwd)) == NULL)
		return (ft_putstr_fd("erreur", 2), 1);
	ft_putstr_fd(pwd, fd);
	ft_putstr_fd("\n", fd);
	return (0);
}

int	ft_env(t_shell *shell)
{
	t_env	*current;

	if (!shell->path)
		return (printf("env: No such file or directory\n"), 0);
	current = shell->enviro;
	while (current)
	{
		if (current->value)
			printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
	return (1);
}