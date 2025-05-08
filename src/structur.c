/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structur.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmetge <rmetge@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 13:16:31 by rmetge            #+#    #+#             */
/*   Updated: 2025/05/08 16:55:20 by rmetge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	arg_addback(t_list **argument, t_list **arg)
{
	char	*new;

	new = ft_strdup(((t_token *)(*arg)->content)->value);
	ft_lstadd_back(argument, ft_lstnew(new));
}

t_cmd	*last_cmd(t_cmd *cmd)
{
	while (cmd && cmd->pipe)
	{
		cmd = cmd->pipe;
	}
	return (cmd);
}

void	addback_cmd(t_cmd **cmd, t_cmd *new)
{
	if (*cmd)
		last_cmd(*cmd)->pipe = new;
	else
		*cmd = new;
}

t_cmd	*structur_cmd(t_shell *shell)
{
	t_cmd	*cmd;
	t_cmd	*new;

	cmd = NULL;
	while (shell->tokens)
	{
		new = cmd_new(shell);
		if (new == NULL)
			return (NULL);
		addback_cmd(&cmd, new);
		if (shell->tokens && ((t_token *)shell->tokens->content)->type == PIPE)
			shell->tokens = shell->tokens->next;
	}
	return (cmd);
}
int	ft_structur(t_shell *shell, char *arg)
{
	shell->tokens = stuctur_token(arg, shell);
	if ((shell->tokens == NULL) || (check_token(shell->tokens) == 1))
		return (printf("Erreur\n"), 1);
	shell->cmd = structur_cmd(shell);
	if (shell->cmd == NULL)
		return (printf("Erreur\n"), 1);
	//check_quote(shell);
	while (shell->cmd)
	{
		int i = 0;
		printf("path = %s\n", (shell->cmd->path));
		printf("argv = ");
		while (shell->cmd->argv[i])
			printf("%s ", (shell->cmd->argv[i++]));
		printf("\n");
		while (shell->cmd->redirection)
		{
			printf("redirection file = %s\n", ((t_redir *)shell->cmd->redirection->content)->file);
			printf("redirection type = %u\n", ((t_redir *)shell->cmd->redirection->content)->type);
			shell->cmd->redirection = shell->cmd->redirection->next;
		}
		shell->cmd = shell->cmd->pipe;
		printf("\n");
	}
	return (0);
}

//demain les ""
