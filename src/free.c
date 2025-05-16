/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemma <bemma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:30:46 by rmetge            #+#    #+#             */
/*   Updated: 2025/05/16 15:17:45 by bemma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(void *token)
{
	free(((t_token *)token)->value);
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

void	free_enviro(t_env **env)
{
	t_env	*tmp;

	while (env && *env)
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

void	free_shell(t_shell **shell)
{
	free_enviro(&(*shell)->enviro);
	free((*shell)->enviro);
	free((*shell));
}
void	free_envr(t_shell **shell)
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
		free_envr(&shell);
	if (shell->path)
	{
		while (shell->path[i])
			free (shell->path[i++]);
		free (shell->path);
	}
}