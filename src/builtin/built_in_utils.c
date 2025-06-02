/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemma <bemma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 09:14:50 by rmetge            #+#    #+#             */
/*   Updated: 2025/06/02 16:31:32 by bemma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_echo(t_cmd *cmd, int i, int fd, int newline)
{
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

int	ft_echo(t_cmd *cmd, int newline, int fd)
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
		while (cmd->argv[i][j] && cmd->argv[i][j] == ' ')
			j++;
		newline = 0;
		if (cmd->argv[i][j])
			break ;
		i++;
	}
	print_echo(cmd, i, fd, newline);
	return (0);
}

int	ft_unset(t_shell *shell, t_cmd *cmd)
{
	t_env	*env;
	t_env	*tmp;
	int		i;

	env = shell->enviro;
	i = 1;
	if (!cmd->argv[1])
		return (0);
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
	return (0);
}

int	ft_pwd(int fd)
{
	char	pwd[1024];

	if (getcwd(pwd, sizeof(pwd)) == NULL)
		return (ft_putstr_fd("erreur", STDERR_FILENO), 1);
	ft_putendl_fd(pwd, fd);
	return (0);
}
