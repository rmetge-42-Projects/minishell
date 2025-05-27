/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmetge <rmetge@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:39:59 by rmetge            #+#    #+#             */
/*   Updated: 2025/05/22 20:17:46 by rmetge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	chang_cdw(t_shell *shell, char *str)
{
	t_env	*env_tmp;

	env_tmp = shell->enviro;
	while (env_tmp && ft_strcmp("OLDPWD", env_tmp->key) != 0)
		env_tmp = env_tmp->next;
	if (env_tmp && ft_strcmp("OLDPWD", env_tmp->key) == 0)
	{
		free(env_tmp->value);
		env_tmp->value = chr_path("PWD", shell->enviro);
	}
	env_tmp = shell->enviro;
	while (shell->enviro && ft_strcmp("PWD", shell->enviro->key) != 0)
		shell->enviro = shell->enviro->next;
	if (shell->enviro && ft_strcmp("PWD", shell->enviro->key) == 0)
	{
		free(shell->enviro->value);
		shell->enviro->value = ft_strdup(str);
	}
	shell->enviro = env_tmp;
}

int	ft_cd(t_shell *shell, char **argv)
{
	char	cwd[1024];
	char	*src;

	if (!argv[1] || ft_strcmp("~", argv[1]) == 0)
		src = chr_path("HOME", shell->enviro);
	else if (ft_strcmp("-", argv[1]) == 0)
	{
		src = chr_path("OLDPWD", shell->enviro);
	}
	else
		src = ft_strdup(argv[1]);
	if (src == NULL)
		return (free(src), printf("cd: argument required\n"), 1);
	if (chdir(src) != 0)
	{
		printf("cd failed: %s\n", src);
		return (free(src), 1);
	}
	getcwd(cwd, sizeof(cwd));
	chang_cdw(shell, cwd);
	free(src);
	return (0);
}
