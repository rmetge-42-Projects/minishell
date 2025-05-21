/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmetge <rmetge@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:15:48 by rmetge            #+#    #+#             */
/*   Updated: 2025/05/20 19:26:26 by rmetge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	quote(int *q0, int *q1, int i, char *src)
{
	if (src[i] == 34 && (*q0) == 0)
	{
		if ((*q1) == 0)
			(*q1) = 1;
		else if ((*q1) == 1)
			(*q1) = 0;
	}
	else if (src[i] == 39 && (*q1) == 0)
	{
		if ((*q0) == 0)
			(*q0) = 1;
		else if ((*q0) == 1)
			(*q0) = 0;
	}
}

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
		if ((src[i] == 34 && q[0] == 0) || (src[i] == 39 && q[1] == 0))
			quote(&q[0], &q[1], i, src);
		else
		{
			dest[j] = src[i];
			j++;
		}
		i++;
	}
	dest[j] = '\0';
	return (dest);
}

void	check_arg(t_shell *shell, char *value)
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
	while (value[i])
	{
		if ((value[i] == 34 && q[0] == 0)
			|| (value[i] == 39 && q[1] == 0))
			quote(&q[0], &q[1], i, (value));
		else
			len++;
		i++;
	}
	dest = cpy_quote(value, len);
	free (((t_token *)shell->tokens->content)->value);
	((t_token *)shell->tokens->content)->value = dest;
}
