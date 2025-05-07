/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmetge <rmetge@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:23:44 by rmetge            #+#    #+#             */
/*   Updated: 2025/05/07 13:48:15 by rmetge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	check_quote(t_shell *shell)
// {
// 	t_list	*new_token;
// 	t_list	*t;

// 	new_token = NULL;
// 	//char	*tmp;
// 	t = shell->tokens;
// 	if (((t_token *)shell->tokens->content)->type == QUOTE2)
// 	{
// 		if (((t_token *)shell->tokens->content)->value[0] == '$')
// 			printf("$$$ = %s", ((t_token *)shell->tokens->content)->value);
// 	}
// 	shell->tokens = shell->tokens->next;
// 	shell->tokens = t;
// }

// // "sans modifier les tokens"