/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmetge <rmetge@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 09:14:50 by rmetge            #+#    #+#             */
/*   Updated: 2025/05/28 11:57:34 by rmetge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_cmd *cmd, int newline, int fd)
{
	int	i;
	int	j;

	i = 1;
	while (cmd->argv[i] != NULL
		&& ft_strncmp(cmd->argv[i], "-n", 2) == 0)
	{
		j = 2;
		while (cmd->argv[i][j] == 'n')
			j++;
		if (cmd->argv[i][j])
			break ;
		i++;
		newline = 0;
	}
	while (cmd->argv[i])
	{
		ft_putstr_fd(cmd->argv[i], fd);
		if (cmd->argv[i + 1] != NULL)
			ft_putstr_fd(" ", fd);
		i++;
	}
	if (newline)
		ft_putstr_fd("\n", fd);
}

void	sup_env(t_env *env, char *argv)
{
	t_env	*tmp;

	while (env->next && ft_strcmp(env->next->key, argv) != 0)
		env = env->next;
	if (env->next && ft_strcmp(env->next->key, argv) == 0)
	{
		tmp = env->next;
		env->next = env->next->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}

void	ft_unset(t_shell *shell, t_cmd *cmd)
{
	t_env	*env;
	t_env	*tmp;
	int		i;

	env = shell->enviro;
	i = 1;
	if (!cmd->argv[1])
		return ;
	while (cmd->argv[i])
	{
		if (env && ft_strcmp(env->key, cmd->argv[i]) == 0)
		{
			tmp = shell->enviro;
			shell->enviro = shell->enviro->next;
			env = shell->enviro;
			free(tmp->key);
			free(tmp->value);
			free(tmp);
		}
		else
			sup_env(env, cmd->argv[i]);
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

	current = shell->enviro;
	while (current)
	{
		if (current->value)
			printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
	return (1);
}
