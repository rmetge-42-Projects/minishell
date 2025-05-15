/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmetge <rmetge@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:23:42 by rmetge            #+#    #+#             */
/*   Updated: 2025/05/15 17:33:42 by rmetge           ###   ########.fr       */
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

char	**env(t_env	*enviro)
{
	char		**env;
	int			i;
	size_t		j;
	int			k;
	int			len;

	i = 0;
	env = ft_calloc(len_env(enviro) + 1, sizeof(char *));
	while(enviro)
	{
		j = 0;
		k = 0;
		len = ft_strlen(enviro->key) + ft_strlen(enviro->value);
		env[i] = ft_calloc(len + 2, sizeof(char));
		while (j < ft_strlen(enviro->key))
		{
			env[i][k++] = enviro->key[j];
			j++;
		}
		j = 0;
		env[i][k++] = '=';
		while (j < ft_strlen(enviro->value))
		{
			env[i][k++] = enviro->value[j];
			j++;
		}
		env[i][k] = '\0';
		enviro = enviro->next;
		i++;
	}
	return (env);
}
