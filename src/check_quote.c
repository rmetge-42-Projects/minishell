/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmetge <rmetge@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:23:44 by rmetge            #+#    #+#             */
/*   Updated: 2025/05/19 19:01:16 by rmetge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	len_dollar(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && (ft_isalnum(arg[i]) || arg[i] == '_'))
		i++;
	return (i);
}

char	*chr_path(char *arg, t_env *enviro)
{
	char	*dollar;

	dollar = ft_calloc(len_dollar(arg) + 1, 1);
	ft_strlcpy(dollar, arg, len_dollar(arg) + 1);
	while (enviro)
	{
		if (ft_strcmp(dollar, enviro->key) == 0)
		{
			free(dollar);
			return (ft_strdup(enviro->value));
		}
		enviro = enviro->next;
	}
	free(dollar);
	return (NULL);
}

char	*ft_dollar(t_shell *shell, char *first)
{
	char	*arg;
	char	*dollar;
	// char	*dollar1;
	// int		i;
	// // int		len;
	// char	*all;
	// char	*tmp;
	// char	*dest;

	/*tmp = NULL;
	dollar = NULL;
	i = len_dollar(ft_strchr(first, '$') + 1);
	// i = 0;
	all = ft_strdup(ft_strchr(first, '$') + 1);
	while (first[i] && first[i] != '$')
		i++;
	if (i < (int)ft_strlen(first))
		arg = ft_strndup(ft_strchr(all, '$') + 1, i - 1);
	printf("%s\n", 	all);
	// printf("%s\n", 	arg);
	// return(NULL);
	while (ft_strchr(all, '$') != NULL)
	{
		printf("arg = %s\n", arg);
		free(dollar);
		dollar = dollar_path(arg, shell->enviro, first);
		free(dollar1);
		dollar1 = ft_strjoin(dest, dollar);
		dest = dollar1;
		printf("dol = %s\n", dollar);
		// i = len_dollar(ft_strchr(arg, '$') + 1);
		free(tmp);
		tmp = ft_strdup(ft_strchr(all, '$') + 1);
		free(all);
		all = tmp;
		i++;
		while (first[i] && first[i] != '$')
			i++;
		if (i < (int)ft_strlen(first))
			arg = ft_strndup(ft_strchr(all, '$') + 1, i - 1);
	}*/

	arg = ft_strdup(ft_strchr(first, '$') + 1);
	dollar = dollar_path(arg, shell->enviro, first);
	return(dollar);
}


t_token	*check_quote(t_shell *shell, int j, const char *s)
{
	enum e_token	arg_type;
	char			*first;
	char			*dest;

	arg_type = token_type(s);
	if (s[0] == 34 || s[0] == 39)
		first = ft_substr(s, 1, j - 2);
	else
		first = ft_substr(s, 0, j);
	if ((arg_type == ARG || arg_type == QUOTE2) && ft_strchr(first, '$'))
	{
		dest = ft_dollar(shell, first);
		free(first);
		return (ft_tokennew(dest, arg_type));
	}
	return (ft_tokennew(first, arg_type));
}