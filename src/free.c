/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmetge <rmetge@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:30:46 by rmetge            #+#    #+#             */
/*   Updated: 2025/05/09 11:17:27 by rmetge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(void *token)
{
	free(((t_token *)token)->value);
}

void	free_redirec(void *redir)
{
	free(((t_redir *)redir)->file);
}

void	free_shell(t_shell **shell)
{
	int	i;

	i = 0;
	// ft_free_split ((*shell)->args);
	// free ((*shell)->line);
	while ((*shell)->path[i])
		free ((*shell)->path[i++]);
	free ((*shell)->path);
	ft_lstclear(&(*shell)->tokens, free_tokens) ;
	while ((*shell)->cmd)
	{
		// free((*shell)->cmd->argv);
		ft_free_split((*shell)->cmd->argv);
		free((*shell)->cmd->path);
		ft_lstclear(&(*shell)->cmd->redirection, free_redirec);
		(*shell)->cmd = (*shell)->cmd->pipe;
	}
	free((*shell)->cmd);
	free((*shell));
}