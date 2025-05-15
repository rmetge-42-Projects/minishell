/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemma <bemma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 11:57:52 by bemma             #+#    #+#             */
/*   Updated: 2025/05/15 09:33:05 by bemma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_or_update_env(t_env **env, char *key, char *value)
{
	t_env	*current;

	current = *env;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			free(current->value);
			if (value)
				current->value = ft_strdup(value);
			else
				current->value = NULL;
			free(key);
			if (value)
				free(value);
			return ;
		}
		current = current->next;
	}
	env_add_back(env, env_new_node(key, value));
}

void	ft_swap_env(t_env *current, t_env *next)
{
	char	*tmp_key;
	char	*tmp_value;

	tmp_key = current->key;
	current->key = next->key;
	next->key = tmp_key;
	tmp_value = current->value;
	current->value = next->value;
	next->value = tmp_value;
}

void	print_copy(t_env *cpy)
{
	while (cpy)
	{
		if (cpy->value)
			printf("declare -x %s=\"%s\"\n", cpy->key, cpy->value);
		else
			printf("declare -x %s\n", cpy->key);
		cpy = cpy->next;
	}
}

void	sort_env(t_shell *shell)
{
	t_env	*cpy;
	t_env	*next;
	t_env	*start;
	t_env	*current;
	int		sort;

	cpy = copy_env_list(*shell->enviro);
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
	free_env(&start);
	return ;
}

void	ft_export(t_shell *shell)
{
	char	**args;
	int		i;
	char	*key;
	char	*value;
	char	*equal_sign;

	args = ft_split(shell->line, ' ');
	if (!args[1])
	{
		sort_env(shell);
		ft_free_split(args);
		return;
	}
	i = 1;
	while (args[i])
	{
		equal_sign = ft_strchr(args[i], '=');
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
			continue ;
		}
		else
			add_or_update_env(shell->enviro, key, value);
		i++;
	}
	ft_free_split(args);
}
