/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemma <bemma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 10:56:07 by bemma             #+#    #+#             */
/*   Updated: 2025/06/02 15:28:34 by bemma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	null_event(void)
{
	return (1);
}

void	putstr_line(int count_line, char *delimiter, char *line)
{
	if (!line)
	{
		ft_putstr_fd("minishell: warning: here-document at line ",
			STDERR_FILENO);
		ft_putnbr_fd(count_line, STDERR_FILENO);
		ft_putstr_fd(" delimited by end-of-file (wanted `", STDERR_FILENO);
		ft_putstr_fd(delimiter, STDERR_FILENO);
		ft_putstr_fd("')\n", STDERR_FILENO);
	}
}
