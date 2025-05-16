/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmetge <rmetge@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 11:57:52 by bemma             #+#    #+#             */
/*   Updated: 2025/05/15 17:52:47 by rmetge           ###   ########.fr       */
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

int	export_env(char **args, int i, t_shell *shell, char *equal_sign)
{
	char	*key;
	char	*value;

	if (equal_sign)
	{
		key = ft_strndup(args[i], equal_sign - args[i]);
		value = ft_strdup(equal_sign + 1);
	}
	else
	{
		key = strdup(args[i]);
		value = NULL;
	}
	if (!key || !is_valid_identifier(key))
	{
		fprintf(stderr, "export: `%s': not a valid identifier\n", args[i]);
		free(key);
		if (value)
			free(value);
		return (1);
	}
	else
		add_or_update_env(&shell->enviro, key, value);
	return (0);
}

void	ft_export(t_shell *shell)
{
	char	**args;
	char	*equal_sign;
	int		i;
	int		res;

	args = ft_split(shell->line, ' ');
	if (!args[1])
	{
		sort_env(copy_env_list(shell->enviro));
		ft_free_split(args);
		return ;
	}
	i = 1;
	while (args[i])
	{
		equal_sign = ft_strchr(args[i], '=');
		res = export_env(args, i, shell, equal_sign);
		if (res == 1)
			continue ;
		i++;
	}
	ft_free_split(args);
}
