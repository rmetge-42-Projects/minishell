/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structur_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmetge <rmetge@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 12:10:11 by rmetge            #+#    #+#             */
/*   Updated: 2025/05/05 16:42:48 by rmetge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*ft_redir(t_list *arg)
{
	t_redir	*redir;
	size_t	len;

	redir = malloc(sizeof(t_redir));
	len = ft_strlen((const char *)((t_token *)arg->content)->value);
	if (ft_strncmp(((t_token *)arg->content)->value, ">", len) == 0)
		redir->type = OUTPUT;
	else if (ft_strncmp(((t_token *)arg->content)->value, "<", len) == 0)
		redir->type = INPUT;
	else if (ft_strncmp(((t_token *)arg->content)->value, ">>", len) == 0)
		redir->type = APPEND;
	else if (ft_strncmp(((t_token *)arg->content)->value, "<<", len) == 0)
		redir->type = HEREDOC;
	redir->file = ((t_token *)arg->next->content)->value;
	return (redir);
}

int	ft_redirect(t_list **arg, t_cmd **cmd)
{
	if (((t_token *)(*arg)->next->content)->type == REDIRECT
		|| (*arg)->next == NULL)
		return(printf("Erreu"), 0);
	ft_lstadd_back(&(*cmd)->redirection, ft_lstnew(ft_redir(*arg)));
	(*arg) = (*arg)->next;
	return (1);
}

char	**ft_element(t_list *element)
{
	char	**argv;
	int		i;

	i = 0;
	argv = malloc((ft_lstsize(element) + 1) * sizeof(char *));
	while (element)
	{
		argv[i++] = ft_strdup(element->content);
		element = element->next;
	}
	argv[i] = NULL;
	return(argv);
}