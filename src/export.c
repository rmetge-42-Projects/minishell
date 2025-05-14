/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmetge <rmetge@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 11:57:52 by bemma             #+#    #+#             */
/*   Updated: 2025/05/14 15:32:16 by rmetge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_strndup(const char *s, size_t n)
{
	char	*dup;
	size_t len;

	// if (!s)
	//     return (NULL);
	len = strnlen(s, n); // Trouve la longueur réelle à copier (max n)
	dup = ft_calloc(len + 1 , sizeof(char)); // Alloue la mémoire pour la nouvelle chaîne
	if (!dup)
		return (NULL);
	ft_memcpy(dup, s, len); // Copie les caractères
	dup[len] = '\0'; // Ajoute le caractère nul de fin
	return (dup);
}

t_env *env_new_node(char *key, char *value)
{
	t_env *new_node;

	new_node = ft_calloc(sizeof(t_env), 1);
	if (!new_node)
		return (free(new_node), NULL);
	new_node->key = key;
	new_node->value = value;
	new_node->next = NULL;
	return (new_node);
}

void env_add_back(t_env **env, t_env *new_node)
{
	t_env *current;

	if (!*env)
	{
		*env = new_node;
		return;
	}
	current = *env;
	while (current->next)
		current = current->next;
	current->next = new_node;
}


void init_env(t_env **env, char **envp)
{
	int     i;
	char    *key;
	char    *value;
	char    *equal_sign;
	t_env   *new_node;

	i = 0;
	while (envp[i])
	{
		equal_sign = ft_strchr(envp[i], '=');
		if (equal_sign)
		{
			key = ft_strndup(envp[i], equal_sign - envp[i]); // Clé avant le '='
			value = ft_strdup(equal_sign + 1);              // Valeur après le '='
			new_node = env_new_node(key, value);
			env_add_back(env, new_node);
		}
		i++;
	}
}

int is_valid_identifier(char *key)
{
	int i;

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

void add_or_update_env(t_env **env, char *key, char *value)
{
	t_env *current;

	current = *env;
	while (current)
	{
		if (strcmp(current->key, key) == 0) // Si la clé existe déjà
		{
			// free(current->value);
			if (value)
				current->value = ft_strdup(value);
			else
				current->value = NULL;
			// free(key);
			return;
		}
		current = current->next;
	}

	// Si la clé n'existe pas, ajoute un nouveau nœud
	env_add_back(env, env_new_node(key, value));
}

void sort_env(t_shell *shell)
{
	char ***cpy;
	t_env *tmp;
	t_env *current;

	int i = 0;
	int len = 0;
	int j = 0;
	tmp = ft_calloc(sizeof(t_env), 1);
	current = *(shell->enviro);
	while (current)
	{
		len++;
		current = current->next;
	}
	cpy = ft_calloc(sizeof(char **), (len + 1));
	current = *(shell->enviro);
	while (current)
	{
		cpy[i] = ft_calloc(sizeof(char *), (3));
		cpy[i][0] = ft_strdup(current->key);
		cpy[i][1] = ft_strdup(current->value);
		cpy[i][2] = NULL;
		current = current->next;
		i++;
	}
	cpy[i] = NULL;
	i = 0;
	while (i < len - 1)
	{
		j = i + 1;
		while (j < len)
		{
			if (strcmp(cpy[i][0], cpy[j][0]) > 0)
			{
				tmp->key = cpy[i][0];
				tmp->value = cpy[i][1];
				cpy[i][0] = cpy[j][0];
				cpy[i][1] = cpy[j][1];
				cpy[j][0] = tmp->key;
				cpy[j][1] = tmp->value;
			}
			j++;
		}
		i++;
	}
	i = 0;
	while (i < len)
	{
		printf("declare -x %s=\"%s\"\n", cpy[i][0], cpy[i][1]);
		i++;
	}
	i = 0;
	while (cpy[i])
	{
		ft_free_split(cpy[i]);
		i++;
	}
	free(cpy);
	free(tmp);
	return;
}
void ft_export(t_shell *shell)
{
	char    **args;
	int     i;
	char    *key;
	char    *value;
	char    *equal_sign;

	args = ft_split(shell->line, ' '); // Divise la commande en arguments
	if (!args[1]) // Si aucun argument, afficher les variables d'environnement
	{
		sort_env(shell);
		// ft_free_split(args);
		return;
	}
	i = 1;
	while (args[i])
	{
		equal_sign = ft_strchr(args[i], '=');
		if (equal_sign) // Cas où une valeur est fournie (key=value)
		{
			key = ft_strndup(args[i], equal_sign - args[i]); // Clé avant le '='
			value = ft_strdup(equal_sign + 1);              // Valeur après le '='
		}
		else // Cas où seule la clé est fournie (key)
		{
			key = strdup(args[i]);
			value = NULL;
		}

		// Vérifie si l'identifiant est valide
		if (!key || !is_valid_identifier(key))
		{
			fprintf(stderr, "export: `%s': not a valid identifier\n", args[i]);
			// free(key);
			// if (value)
				// free(value);
			continue ;
		}
		else
			add_or_update_env(shell->enviro, key, value);
		i++;
	}
	ft_free_split(args);
}