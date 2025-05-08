/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemma <bemma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 11:02:57 by rmetge            #+#    #+#             */
/*   Updated: 2025/05/08 12:59:48 by bemma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_line_centered(char *line, int term_width)
{
	int	len;
	int	spaces;

	len = ft_strlen(line);
	spaces = (term_width - len) / 2;
	if (spaces < 0)
		spaces = 0;
	printf("%*s\033[1;38;5;205m%s\033[0m\n", spaces, "", line);
}

void	print_header(void)
{
	struct winsize	ws;
	char			*lines[8];
	int				i;

	lines[0] = "                                                                       _    ";
	lines[1] = "        ,--.   ,--.,--.        ,--.       ,--.            ,--.,--.   _( )_  ";
	lines[2] = "        |   `.'   |`--',--,--, `--' ,---. |  ,---.  ,---. |  ||  |  (_ o _) ";
	lines[3] = "   _    |  |'.'|  |,--.|      |,--.(  .-' |  .-.  || .-. :|  ||  |   (_,_)  ";
	lines[4] = " _( )_  |  |   |  ||  ||  ||  ||  |.-'  `)|  | |  ||   --.|  ||  |          ";
	lines[5] = "(_ o _) `--'   `--'`--'`--''--'`--'`----' `--' `--' `----'`--'`--'          ";
	lines[6] = " (_,_)                                                                      ";
	lines[7] = "                                                                            ";
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
	i = 0;
	while (i < 8)
	{
		print_line_centered(lines[i], ws.ws_col);
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	char *mini;
	t_shell	*shell;
	volatile sig_atomic_t g_sigint = 0;
	(void)argc;
	(void)argv;

	print_header();
	shell = ft_calloc(1, sizeof(t_shell));
	shell->path = ft_path(envp);
	shell->env = envp;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_ctrl_c);
	
	while (1)
	{
		mini = readline("\001\033[38;5;205m\002minishell> \001\033[0m\002");
		if (!mini)
			break;
		shell->line = mini;
		shell->args = ft_split(shell->line, ' ');
		if (g_sigint)
		{
			g_sigint = 0;
			free(mini);
			continue;
		}
		if (*mini)
			add_history(mini);
		if (!shell->args || !shell->args[0])
		{
			free(mini);
			ft_f_s(shell->args);
			continue;
		}
		if (ft_exit(shell) == 1)
			break ;
		ft_structur(shell, mini);
		ft_pipex(shell);
	}
	printf("Bye 👋\n");
	return 0;
}
