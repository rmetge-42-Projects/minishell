/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemma <bemma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:23:42 by rmetge            #+#    #+#             */
/*   Updated: 2025/06/02 16:28:13 by bemma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	len_env(t_env	*enviro)
{
	int	i;

	i = 0;
	while (enviro)
	{
		i++;
		enviro = enviro->next;
	}
	return (i);
}

char	*cpy_env(t_env *enviro)
{
	size_t		j;
	int			k;
	int			len;
	char		*dest;

	j = 0;
	k = 0;
	len = ft_strlen(enviro->key);
	if (enviro->value)
		len += ft_strlen(enviro->value);
	dest = ft_calloc(len + 2, sizeof(char));
	while (j < ft_strlen(enviro->key))
	{
		dest[k++] = enviro->key[j];
		j++;
	}
	j = 0;
	dest[k++] = '=';
	if (enviro->value)
	{
		while (j < ft_strlen(enviro->value))
			dest[k++] = enviro->value[j++];
	}
	dest[k] = '\0';
	return (dest);
}

char	**env(t_env	*enviro)
{
	char		**env;
	int			i;

	i = 0;
	env = ft_calloc(len_env(enviro) + 1, sizeof(char *));
	while (enviro)
	{
		env[i] = cpy_env(enviro);
		enviro = enviro->next;
		i++;
	}
	return (env);
}

int	ft_env(t_shell *shell)
{
	t_env	*current;

	if (!shell->path)
		return (ft_putendl_fd("env: No such file or directory",
				STDERR_FILENO), 0);
	current = shell->enviro;
	while (current)
	{
		if (current->value)
			printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
	return (1);
}
