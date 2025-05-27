/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structur_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmetge <rmetge@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 13:16:31 by rmetge            #+#    #+#             */
/*   Updated: 2025/05/27 15:51:45 by rmetge           ###   ########.fr       */
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

int	structur_cmd(t_shell *shell)
{
	t_cmd	*new;

	shell->cmd = NULL;
	while (shell->tokens)
	{
		new = cmd_new(shell);
		if (new == NULL)
			return (0);
		addback_cmd(&shell->cmd, new);
		if (shell->tokens && ((t_token *)shell->tokens->content)->type == PIPE)
			shell->tokens = shell->tokens->next;
	}
	return (1);
}

int	ft_structur(t_shell *shell, char *arg)
{
	t_list	*t;

	shell->env = env(shell->enviro);
	ft_path(shell);
	shell->tokens = stuctur_token(arg, shell);
	t = shell->tokens;
	if ((shell->tokens == NULL) || (check_token(shell->tokens) == 1))
	{
		free_all(shell, arg);
		return (ft_lstclear(&shell->tokens, free_tokens), 1);
	}
	// while (shell->tokens->content)
	// {
	// 	printf("%s\n", ((t_token *)shell->tokens->content)->value);
	// 	printf("%u\n", ((t_token *)shell->tokens->content)->type);
	// 	shell->tokens = shell->tokens->next;
	// }
	// return (1);
	// printf("i");
	structur_cmd(shell);
	shell->tokens = t;
	ft_lstclear(&shell->tokens, free_tokens);
	if (shell->cmd == 0)
		return (free_all(shell, arg), 1);
	// while (shell->cmd)
	// {
	// 	int i = 0;
	// 	printf("path = %s\n", (shell->cmd->path));
	// 	printf("argv = ");
	// 	while (shell->cmd->argv[i])
	// 		printf("%s ", (shell->cmd->argv[i++]));
	// 	printf("\n");
	// 	while (shell->cmd->redirection)
	// 	{
	// 		printf("redirection file = %s\n", ((t_redir *)shell->cmd->redirection->content)->file);
	// 		printf("redirection type = %u\n", ((t_redir *)shell->cmd->redirection->content)->type);
	// 		shell->cmd->redirection = shell->cmd->redirection->next;
	// 	}
	// 	shell->cmd = shell->cmd->pipe;
	// 	printf("\n");
	// }
	return (0);
}
