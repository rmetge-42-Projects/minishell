/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_two.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemma <bemma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:00:24 by rmetge            #+#    #+#             */
/*   Updated: 2025/05/30 13:25:17 by bemma            ###   ########.fr       */
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

// void	print_copy(t_env *cpy)
// {
// 	while (cpy)
// 	{
// 		if (cpy->value)
// 		{
// 			char *val = cpy->value;
// 			size_t len = ft_strlen(val);

// 			// Vérifie si la valeur est entourée de guillemets
// 			if (len >= 2 && val[0] == '"' && val[len - 1] == '"')
// 			{
// 				// Affiche sans les guillemets
// 				char *clean_val = ft_strndup(val + 1, len - 2);
// 				printf("declare -x %s=\"%s\"\n", cpy->key, clean_val);
// 				free(clean_val);
// 			}
// 			else
// 			{
// 				// Affiche normalement
// 				printf("declare -x %s=\"%s\"\n", cpy->key, val);
// 			}
// 		}
// 		else
// 			printf("declare -x %s\n", cpy->key);

// 		cpy = cpy->next;
// 	}
// }
