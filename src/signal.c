/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemma <bemma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 13:54:04 by bemma             #+#    #+#             */
/*   Updated: 2025/05/20 16:27:59 by bemma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig;

int	check_ctrl_c_h(void)
{
	if (g_sig != SIGINT)
		return (1);
	return (0);
}

void	ft_ctrl_c(int sig)
{
	if (g_sig == 1 && sig == SIGINT)
	{
		ft_putstr_fd("^C", 1);
		g_sig = SIGINT;
		rl_done = 1;
		
	}
	else if (g_sig != 1 && sig == SIGINT)
	{
		if (waitpid(-1, NULL, WNOHANG) == -1)
		{
			ft_putstr_fd("^C\n", 1);
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
		else
			ft_putstr_fd("\n", 1);
		g_sig = SIGINT;
	}
}
void	ft_ctrl_backslash(int sig)
{
	if ((waitpid(-1, NULL, WNOHANG) == -1 && sig == SIGQUIT) || (g_sig == 1 && sig == SIGQUIT))
	{
		rl_done = 1;
		g_sig = SIGQUIT;
		return ;
	}
	else if (g_sig != 1)
	{
		ft_putstr_fd("Quit (core dumped)\n", 1);
		g_sig = SIGQUIT;
	}
}

void	manege_signal(void)
{
	if (SIGINT)
		signal(SIGINT, ft_ctrl_c);
	if (SIGQUIT)
		signal(SIGQUIT, ft_ctrl_backslash);
}
