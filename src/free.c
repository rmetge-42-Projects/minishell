/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmetge <rmetge@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:30:46 by rmetge            #+#    #+#             */
/*   Updated: 2025/05/14 18:14:21 by rmetge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(void *token)
{
	// if (((t_token *)token)->value)
	free(((t_token *)token)->value);
	// if ((t_token *)token)
	free((t_token *)token);
}

void	free_redirec(void *redir)
{
	free(((t_redir *)redir)->file);
	free((t_redir *)redir);
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
	free_env((*shell)->enviro);
	free((*shell)->enviro);
	free((*shell));
}

void	free_env(t_env **env)
{
	t_env	*tmp;

	while(env && *env)
	{
		if ((*env)->key)
			free((*env)->key);
		if ((*env)->value)
			free((*env)->value);
		tmp = (*env)->next;
		free((*env));
		(*env) = tmp;
	}
}

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
