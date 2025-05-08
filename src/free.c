/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmetge <rmetge@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:30:46 by rmetge            #+#    #+#             */
/*   Updated: 2025/05/08 19:14:45 by rmetge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(void *token)
{
	free(((t_token *)token)->value);
}

void	free_shell(t_shell **shell)
{
	int	i;

	i = 0;
	free ((*shell)->args);
	// free ((*shell)->env);
	// free ((*shell)->enviro);
	free ((*shell)->line);
	while ((*shell)->path[i])
		free ((*shell)->path[i++]);
	free ((*shell)->path);
	ft_lstclear(&(*shell)->tokens, free_tokens) ;
	//ft_free_tokens(&(*shell)->tokens);
	while ((*shell)->cmd)
	{
		free((*shell)->cmd->argv);
		free((*shell)->cmd->path);
		free((*shell)->cmd->redirection);
		(*shell)->cmd = (*shell)->cmd->pipe;
	}
	free((*shell)->cmd);
	free((*shell));
}