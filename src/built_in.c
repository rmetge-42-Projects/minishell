/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemma <bemma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:17:53 by bemma             #+#    #+#             */
/*   Updated: 2025/05/12 19:54:27 by bemma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *strndup(const char *s, size_t n)
{
    char *dup;
    size_t len;

    // if (!s)
    //     return (NULL);
    len = strnlen(s, n); // Trouve la longueur réelle à copier (max n)
    dup = malloc(len + 1); // Alloue la mémoire pour la nouvelle chaîne
    if (!dup)
        return (NULL);
    memcpy(dup, s, len); // Copie les caractères
    dup[len] = '\0'; // Ajoute le caractère nul de fin
    return (dup);
}

void	ft_ctrl_c(int sig)
{
	(void)sig;

	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	ft_exit(t_shell *shell)
{
	char	**args;

	args = ft_split(shell->line, ' ');
	if (ft_strncmp(args[0], "exit", 5) == 0)
		return (ft_free_split(args), 1);
	return (ft_free_split(args), 0);
}

t_env *env_new_node(char *key, char *value)
{
    t_env *new_node;

    new_node = malloc(sizeof(t_env));
    if (!new_node)
        return (NULL);
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

    i = 0;
    while (envp[i])
    {
        equal_sign = strchr(envp[i], '=');
        if (equal_sign)
        {
            key = strndup(envp[i], equal_sign - envp[i]); // Clé avant le '='
            value = strdup(equal_sign + 1);              // Valeur après le '='
            env_add_back(env, env_new_node(key, value));
        }
        i++;
    }
}

int is_valid_identifier(char *key)
{
    if (!key || (!isalpha(key[0]) && key[0] != '_'))
        return (0);
    for (int i = 1; key[i]; i++)
    {
        if (!isalnum(key[i]) && key[i] != '_')
            return (0);
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
            free(current->value);
            if (value)
                current->value = strdup(value);
            else
                current->value = NULL;
            free(key);
            return;
        }
        current = current->next;
    }

    // Si la clé n'existe pas, ajoute un nouveau nœud
    env_add_back(env, env_new_node(key, value));
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
        t_env *current = *(shell->enviro);
        while (current)
        {
            printf("declare -x %s=\"%s\"\n", current->key, current->value);
            current = current->next;
        }
        ft_free_split(args);
        return;
    }

    i = 1;
    while (args[i])
    {
        equal_sign = strchr(args[i], '=');
        if (equal_sign) // Cas où une valeur est fournie (key=value)
        {
            key = strndup(args[i], equal_sign - args[i]); // Clé avant le '='
            value = strdup(equal_sign + 1);              // Valeur après le '='
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
            free(key);
            if (value)
                free(value);
            continue ;
        }
        else
        {
            // Ajoute ou met à jour la variable d'environnement
            add_or_update_env(shell->enviro, key, value);
        }
        i++;
    }
    // update_envp(shell); // Met à jour le tableau envp
    ft_free_split(args);
}