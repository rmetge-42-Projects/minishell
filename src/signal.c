/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemma <bemma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 13:54:04 by bemma             #+#    #+#             */
/*   Updated: 2025/05/21 17:28:30 by bemma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	g_sig;

int	check_ctrl_h(void)
{
	if (g_sig == 0)
		return (1);
	// if (g_sig != SIGQUIT)
	// 	return (1);
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
	if (g_sig == 1)
		return ;
		
	else if (g_sig != 1 && sig == SIGQUIT)
	{
		dprintf(3, "test");
		dprintf(3, "%d\n", g_sig);
		
			
		if (waitpid(-1, NULL, WNOHANG) != -1)
		{
			// ft_putnbr_fd(g_sig, 2);
			
			ft_putstr_fd("Quit (core dumped)\n", 2);
			// rl_replace_line("", 0);
			// rl_on_new_line();
			g_sig = SIGQUIT;
			
		}
		else
			return ;
		
	}
	
}

void	manege_signal(void)
{
	if (SIGINT)
		signal(SIGINT, ft_ctrl_c);
	if (SIGQUIT)
		signal(SIGQUIT, ft_ctrl_backslash);
	dprintf(3, "testtttttttttt");
}
