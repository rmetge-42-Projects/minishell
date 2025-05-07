/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmetge <rmetge@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 11:02:57 by rmetge            #+#    #+#             */
/*   Updated: 2025/05/07 15:41:39 by rmetge           ###   ########.fr       */
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

	(void)argc;
	(void)argv;
	print_header();
	shell = ft_calloc(1, sizeof(t_shell));
	shell->path = ft_path(envp);
	shell->env = envp;
	while (1)
	{
		mini = readline("\001\033[38;5;205m\002minishell> \001\033[0m\002");
		shell->line = mini;
		if (!mini)
			break;
		if (*mini)
			add_history(mini);
		if (ft_exit(shell) == 1)
			break ;
		ft_structur(shell, mini);
		ft_pipex(shell);
	}
	printf("Bye 👋\n");
	return 0;
}