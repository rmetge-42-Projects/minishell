/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmetge <rmetge@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:23:42 by rmetge            #+#    #+#             */
/*   Updated: 2025/05/26 15:57:03 by rmetge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
