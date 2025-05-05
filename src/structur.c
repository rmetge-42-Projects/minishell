/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structur.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmetge <rmetge@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 13:16:31 by rmetge            #+#    #+#             */
/*   Updated: 2025/05/05 14:36:22 by rmetge           ###   ########.fr       */
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
	char	*f_path;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	element = (t_list *)malloc(sizeof(t_list));
	cmd->redirection = (t_list *)malloc(sizeof(t_list));
	cmd->redirection = NULL; //regarde si en malloc cmd ca malloc redicec?
	cmd = NULL;
	path = 0;
	element = NULL;
	while (shell->tokens)
	{
		if (((t_token *)shell->tokens->content)->type == REDIRECT)
			ft_redirect(&shell->tokens, &cmd);
		else if (((t_token *)shell->tokens->content)->type == PIPE)
		{

		}
		else if (path == 0)
		{
			f_path = ft_find_path(shell->path, shell->tokens->content);
			cmd->path = ft_strdup(f_path);
			path = 1;
			ft_new_element(&element, &shell->tokens);
		}
		else
			ft_new_element(&element, &shell->tokens);

		shell->tokens = shell->tokens->next;
		/*le rest c'est une commande te je remplis de path et le shell->tokenss avec
		l'element, le seul truc qui separ une redirection c'est un pipe*/
	}
	cmd->argv = ft_element(element);
	ft_lstclear(&element, free);
	return (cmd);
}

int	ft_struc(t_shell *shell, char *arg)
{
	t_cmd	*cmd;

	shell->tokens = ft_splitttt(arg);
	if (shell->tokens == NULL)
		return (printf("Erreur\n"), 1);
	cmd = struc_cmd(shell);
	// while (shell->tokens)
	// {
	// 	printf("%s\n", ((t_token *)shell->tokens->content)->value);
	// 	printf("%i\n", ((t_token *)shell->tokens->content)->type);
	// 	shell->tokens = shell->tokens->next;
	// }
	return (0);
}
