/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structur_utile.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmetge <rmetge@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 12:10:11 by rmetge            #+#    #+#             */
/*   Updated: 2025/05/21 09:05:54 by rmetge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*wich_redirect(t_list *arg)
{
	t_redir	*redir;
	size_t	len;

	redir = ft_calloc(1, sizeof(t_redir));
	len = ft_strlen((const char *)((t_token *)arg->content)->value);
	if (ft_strncmp(((t_token *)arg->content)->value, ">", len) == 0)
		redir->type = OUTPUT;
	else if (ft_strncmp(((t_token *)arg->content)->value, "<", len) == 0)
		redir->type = INPUT;
	else if (ft_strncmp(((t_token *)arg->content)->value, ">>", len) == 0)
		redir->type = APPEND;
	else if (ft_strncmp(((t_token *)arg->content)->value, "<<", len) == 0)
		redir->type = HEREDOC;
	redir->file = ft_strdup(((t_token *)arg->next->content)->value);
	return (redir);
}

int	stuctur_redicection(t_list **arg, t_cmd **cmd)
{
	if (((t_token *)(*arg)->next->content)->type == REDIRECT
		|| (*arg)->next == NULL)
		return (printf("Erreur"), 0);
	ft_lstadd_back(&(*cmd)->redirection, ft_lstnew(wich_redirect(*arg)));
	(*arg) = (*arg)->next;
	return (1);
}

char	**str_arg(t_list *element)
{
	char	**argv;
	int		i;

	i = 0;
	argv = ft_calloc((ft_lstsize(element) + 1), sizeof(char *));
	while (element)
	{
		argv[i++] = ft_strdup(element->content);
		element = element->next;
	}
	argv[i] = NULL;
	return (argv);
}

int	path_cmd(t_shell *shell, t_cmd *cmd, t_list **argument)
{
	t_token	*t;

	t = shell->tokens->content;
	cmd->path = ft_find_path_cmd(shell->path, t->value);
	if (cmd->path == NULL)
		return (0);
	arg_addback(argument, &shell->tokens);
	return (1);
}

t_cmd	*cmd_new(t_shell *shell)
{
	t_cmd	*cmd;
	int		path;
	t_list	*argument;

	cmd = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	argument = NULL;
	cmd->redirection = NULL;
	path = 0;
	while (shell->tokens && ((t_token *)shell->tokens->content)->type != PIPE)
	{
		check_arg(shell, ((t_token *)shell->tokens->content)->value);
		if (((t_token *)shell->tokens->content)->type == REDIRECT)
			stuctur_redicection(&shell->tokens, &cmd);
		else if (path == 0)
		{
			path = path_cmd(shell, cmd, &argument);
			if (path == 0)
				return (free(cmd), ft_lstclear(&argument, free), NULL);
		}
		else
			arg_addback(&argument, &shell->tokens);
		shell->tokens = shell->tokens->next;
	}
	cmd->argv = str_arg(argument);
	return (ft_lstclear(&argument, free), cmd);
}
