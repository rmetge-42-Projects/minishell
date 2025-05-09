/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmetge <rmetge@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 11:02:57 by rmetge            #+#    #+#             */
/*   Updated: 2025/05/09 15:42:13 by rmetge           ###   ########.fr       */
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

int	check_readline(t_shell *shell, char *mini)
{
	volatile sig_atomic_t g_sigint = 0;

	shell->line = mini;
	shell->args = ft_split(mini, ' ');
	if (g_sigint)
	{
		g_sigint = 0;
		ft_free_split(shell->args);
		free(mini);
		return (1);
	}
	if (*mini)
		add_history(mini);
	if (!shell->args || !shell->args[0])
	{
		free(mini);
		ft_free_split(shell->args);
		return (1);
	}
	if (ft_exit(shell) == 1)
	{
		ft_free_split(shell->args);
		return (2);
	}
	return (0);
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
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_ctrl_c);
	while (1)
	{
		// shell->tokens = stuctur_token("ls -la", shell);
		// ft_lstclear(&shell->tokens, free_tokens);
		// break; ;
		mini = readline("\001\033[38;5;205m\002minishell> \001\033[0m\002");
		if (!mini)
			break;
		if (check_readline(shell, mini) == 1)
			continue;
		else if (check_readline(shell, mini) == 2)
			break;
		ft_structur(shell, mini);
		ft_pipex(shell);
	// free(mini);
	}
	free_shell(&shell);
	printf("Bye 👋\n");
}
