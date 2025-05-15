/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utile.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmetge <rmetge@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:59:26 by rmetge            #+#    #+#             */
/*   Updated: 2025/05/15 12:00:56 by rmetge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all(t_shell *shell, char *mini)
{
	if (shell->args)
		ft_free_split(shell->args);
	if (mini)
		free(mini);
	if (shell->cmd)
		free_cmd(&shell->cmd);
	if (shell->tokens)
		ft_lstclear(&shell->tokens, free_tokens);
}
