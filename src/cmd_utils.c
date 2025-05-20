/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmetge <rmetge@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:15:48 by rmetge            #+#    #+#             */
/*   Updated: 2025/05/20 17:50:15 by rmetge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	*cpy_quote(char *src, int len)
// {
// 	int		i;
// 	int		j;
// 	char	*dest;

// 	dest = ft_calloc(len + 1, sizeof(char));
// 	i = 0;
// 	j = 0;
// 	while (src[i])
// 	{
// 		if (src[i] != 39 && src[i] != 34)
// 			dest[j++] = src[i++];
// 		else
// 			i++;
// 	}
// 	dest[j] = '\0';
// 	return (dest);
// }

// void	check_arg(t_shell *shell)
// {
// 	int		i;
// 	int		len;
// 	char	*dest;

// 	i = 0;
// 	len = 0;
// 	while (((t_token *)shell->tokens->content)->value[i])
// 	{
// 		if (((t_token *)shell->tokens->content)->value[i] != 39
// 			&& ((t_token *)shell->tokens->content)->value[i] != 34)
// 			len++;
// 		i++;
// 	}
// 	dest = cpy_quote(((t_token *)shell->tokens->content)->value, len);
// 	free (((t_token *)shell->tokens->content)->value);
// 	((t_token *)shell->tokens->content)->value = dest;
// }

char	*cpy_quote(char *src, int len)
{
	char	*dest;
	int		i;
	int		j;
	int		q[2];

	q[0] = 0;
	q[1] = 0;
	i = 0;
	j = 0;
	dest = ft_calloc(len + 1, sizeof(char));
	while (src[i])
	{
		if (src[i] == 34 && q[0] == 0)
		{
			if (q[1] == 0)
				q[1] = 1;
			else if (q[1] == 1)
				q[1] = 0;
		}
		else if (src[i] == 39 && q[1] == 0)
		{
			if (q[0] == 0)
				q[0] = 1;
			else if (q[0] == 1)
				q[0] = 0;
		}
		else
		{
			dest[j] = src[i];
			j++;
		}
		i++;
	}
	dest[j] = '\0';
	return(dest);
}

void	check_arg(t_shell *shell)
{
	int		i;
	int		j;
	int		len;
	char	*dest;
	int		q[2];

	i = 0;
	j = 0;
	len = 0;
	q[0] = 0;
	q[1] = 0;
	while (((t_token *)shell->tokens->content)->value[i])
	{
		if (((t_token *)shell->tokens->content)->value[i] == 34 && q[0] == 0)
		{
			if (q[1] == 0)
				q[1] = 1;
			else if (q[1] == 1)
				q[1] = 0;
			i++;
		}
		else if (((t_token *)shell->tokens->content)->value[i] == 39 && q[1] == 0)
		{
			if (q[0] == 0)
				q[0] = 1;
			else if (q[0] == 1)
				q[0] = 0;
			i++;
		}
		else
		{
			i++;
			len++;
		}
	}
	dest = cpy_quote(((t_token *)shell->tokens->content)->value, len);
	free (((t_token *)shell->tokens->content)->value);
	((t_token *)shell->tokens->content)->value = dest;
}
