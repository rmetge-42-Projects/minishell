/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmetge <rmetge@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:00:23 by bemma             #+#    #+#             */
/*   Updated: 2025/05/15 15:49:52 by rmetge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*env_new_node(char *key, char *value)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = key;
	new_node->value = value;
	new_node->next = NULL;
	return (new_node);
}

void	env_add_back(t_env **env, t_env *new_node)
{
	t_env	*current;

	if (!*env)
	{
		*env = new_node;
		return ;
	}
	current = *env;
	while (current->next)
		current = current->next;
	current->next = new_node;
}

void	init_env(t_env **env, char **envp)
{
	int		i;
	char	*key;
	char	*value;
	char	*equal_sign;
	t_env	*new_node;

	i = 0;
	while (envp[i])
	{
		equal_sign = ft_strchr(envp[i], '=');
		if (equal_sign)
		{
			key = ft_strndup(envp[i], equal_sign - envp[i]);
			value = ft_strdup(equal_sign + 1);
			new_node = env_new_node(key, value);
			env_add_back(env, new_node);
		}
		i++;
	}
}

int	is_valid_identifier(char *key)
{
	int	i;

	if (!key || (!ft_isalpha(key[0]) && key[0] != '_'))
		return (0);
	i = 1;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

t_env	*copy_env_list(t_env *env)
{
	t_env	*copy;
	t_env	*new_node;
	char	*new_key;
	char	*new_value;

	copy = NULL;
	while (env)
	{
		new_key = ft_strdup(env->key);
		if (env->value == NULL)
			new_value = NULL;
		else
			new_value = ft_strdup(env->value);
		new_node = env_new_node(new_key, new_value);
		if (!new_node)
			return (free(new_key), free(new_value), free_env(&copy), NULL);
		if (!copy)
			copy = new_node;
		else
			env_add_back(&copy, new_node);
		env = env->next;
	}
	return (copy);
}
