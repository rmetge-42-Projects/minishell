/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemma <bemma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 11:57:52 by bemma             #+#    #+#             */
/*   Updated: 2025/06/02 15:26:52 by bemma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sort_env(t_env *cpy)
{
	t_env	*next;
	t_env	*start;
	t_env	*current;
	int		sort;

	sort = 0;
	start = cpy;
	while (sort == 0)
	{
		sort = 1;
		current = cpy;
		while (current && current->next)
		{
			next = current->next;
			if (ft_strcmp(current->key, next->key) > 0)
			{
				ft_swap_env(current, next);
				sort = 0;
			}
			current = current->next;
		}
	}
	print_copy(cpy);
	free_enviro(&start);
	return ;
}

void	error_export(char **args, int i)
{
	ft_putstr_fd("export: `", STDERR_FILENO);
	ft_putstr_fd(args[i], STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
}

char	*init_for_export(char *equal_sign)
{
	char	*raw_value;
	char	*value;

	raw_value = equal_sign + 1;
	if (raw_value[0] == '"' && raw_value[ft_strlen(raw_value) - 1] == '"')
		value = ft_strndup(raw_value + 1, ft_strlen(raw_value) - 2);
	else
		value = ft_strdup(raw_value);
	return (value);
}

int	export_env(t_cmd *cmd, int i, t_shell *shell, char *equal_sign)
{
	char	*key;
	char	*value;

	if (equal_sign)
	{
		key = ft_strndup(cmd->argv[i], equal_sign - cmd->argv[i]);
		value = init_for_export(equal_sign);
	}
	else
	{
		key = strdup(cmd->argv[i]);
		value = NULL;
	}
	if (!key || !is_valid_identifier(key))
	{
		error_export(cmd->argv, i);
		free(key);
		if (value)
			free(value);
		return (1);
	}
	else
		add_or_update_env(&shell->enviro, key, value);
	return (0);
}

int	ft_export(t_shell *shell, t_cmd *cmd)
{
	char	*equal_sign;
	int		i;
	int		res;

	if (!cmd->argv[1])
	{
		sort_env(copy_env_list(shell->enviro));
		return (0);
	}
	i = 1;
	while (cmd->argv[i])
	{
		equal_sign = ft_strchr(cmd->argv[i], '=');
		res = export_env(cmd, i, shell, equal_sign);
		i++;
		if (res == 1)
			continue ;
	}
	if (res == 1)
		return (1);
	return (0);
}
