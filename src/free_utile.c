/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utile.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmetge <rmetge@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:59:26 by rmetge            #+#    #+#             */
/*   Updated: 2025/05/16 11:37:55 by rmetge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_shell **shell)
{
	int	j;

	j = 0;
	while ((*shell)->env[j])
		free ((*shell)->env[j++]);
	free ((*shell)->env);
}

void	free_all(t_shell *shell, char *mini)
{
	int	i;

	i = 0;
	if (shell->args)
		ft_free_split(shell->args);
	if (mini)
		free(mini);
	if (shell->cmd)
		free_cmd(&shell->cmd);
	if (shell->tokens)
		ft_lstclear(&shell->tokens, free_tokens);
	if (shell->env)
		free_env(&shell);
	if (shell->path)
	{
		while (shell->path[i])
			free (shell->path[i++]);
		free (shell->path);
	}
}
