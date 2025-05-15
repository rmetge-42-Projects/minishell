/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemma <bemma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:17:53 by bemma             #+#    #+#             */
/*   Updated: 2025/05/15 16:41:37 by bemma            ###   ########.fr       */
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
		rl_done = 1;
		g_sig = SIGINT;
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

void	manege_signal(void)
{
	if (SIGINT)
		signal(SIGINT, ft_ctrl_c);
}

int	ft_exit(t_shell *shell)
{
	char	**args;

	args = ft_split(shell->line, ' ');
	if (ft_strncmp(args[0], "exit", 5) == 0)
		return (ft_free_split(args), 1);
	return (ft_free_split(args), 0);
}
