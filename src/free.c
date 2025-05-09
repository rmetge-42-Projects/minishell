/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmetge <rmetge@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:30:46 by rmetge            #+#    #+#             */
/*   Updated: 2025/05/09 15:55:54 by rmetge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(void *token)
{
	if (((t_token *)token)->value)
		free(((t_token *)token)->value);
	if (token)
		free(token);
}

void	free_redirec(void *redir)
{
	free(((t_redir *)redir)->file);
}

void	free_cmd(t_cmd **cmd)
{
	t_cmd	*tmp;

	while (cmd && *cmd)
	{
		ft_free_split((*cmd)->argv);
		if ((*cmd)->path)
			free((*cmd)->path);
		ft_lstclear(&(*cmd)->redirection, free_redirec);
		tmp = (*cmd)->pipe;
		free((*cmd));
		(*cmd) = tmp;
	}
}

void	free_shell(t_shell **shell)
{
	int	i;

	i = 0;
	while ((*shell)->path[i])
		free ((*shell)->path[i++]);
	free ((*shell)->path);
	// ft_lstclear(&(*shell)->tokens, free_tokens);

	free_cmd(&(*shell)->cmd);
	free((*shell));
}
