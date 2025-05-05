/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structur.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmetge <rmetge@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 13:16:31 by rmetge            #+#    #+#             */
/*   Updated: 2025/05/05 17:09:31 by rmetge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_new_element(t_list **element, t_list **arg)
{
	char	*new;

	new = ft_strdup(((t_token *)(*arg)->content)->value);
	ft_lstadd_back(element, ft_lstnew(new));
}

t_cmd	*struc_cmd(t_shell *shell)
{
	t_cmd	*cmd;
	int		path;
	t_list	*element;
	t_token	*t;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	element = NULL;
	cmd->redirection = NULL;
	path = 0;
	while (shell->tokens)
	{
		if (((t_token *)shell->tokens->content)->type == REDIRECT)
			ft_redirect(&shell->tokens, &cmd);
		else if (((t_token *)shell->tokens->content)->type == PIPE)
		{
			cmd = cmd->pipe;
			path = 0;
			cmd->argv = ft_element(element);
			ft_lstclear(&element, NULL);
			/*trouver une solution pour le pipe, pour pa perdre le debut de cmd,
			faire une autre fonction qui cree des cmd et qui les ajoutre a la suite*/
		}
		else if (path == 0 && ((t_token *)shell->tokens->content)->type == ARG)
		{
			t = shell->tokens->content;
			cmd->path = ft_find_path(shell->path, t->value);
			if (cmd->path == NULL)
				return(printf("Eurrer"), NULL);
			path = 1;
			ft_new_element(&element, &shell->tokens);
		}
		else
			ft_new_element(&element, &shell->tokens);

		shell->tokens = shell->tokens->next;
	}
	cmd->argv = ft_element(element);
	ft_lstclear(&element, free);
	return (cmd);
}

int	ft_struc(t_shell *shell, char *arg)
{
	shell->tokens = ft_splitttt(arg);
	if (shell->tokens == NULL)
		return (printf("Erreur\n"), 1);
	shell->cmd = struc_cmd(shell);
	if (shell->cmd == NULL)
		return (1);
	int i = 0;
	printf("path = %s\n", (shell->cmd->path));
	while (shell->cmd->argv[i])
		printf("argv = %s\n", (shell->cmd->argv[i++]));

	while (shell->cmd->redirection)
	{
		printf("redirection file = %s\n", ((t_redir *)shell->cmd->redirection->content)->file);
		printf("redirection type = %u\n", ((t_redir *)shell->cmd->redirection->content)->type);
		shell->cmd->redirection = shell->cmd->redirection->next;
	}
	return (0);
}
