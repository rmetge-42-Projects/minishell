/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmetge <rmetge@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 11:02:57 by rmetge            #+#    #+#             */
/*   Updated: 2025/05/28 12:04:29 by rmetge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_sig;

int	check_readline(t_shell *shell, char *mini)
{
	shell->line = mini;
	shell->args = ft_split(mini, ' ');
	if (*mini)
		add_history(mini);
	if (!shell->args || !shell->args[0])
		return (1);
	if (ft_exit(shell) == 1)
		return (ft_free_split(shell->args), free(mini), 2);
	return (0);
}

t_shell	*shell_crl(char **envp)
{
	t_shell	*shell;

	shell = ft_calloc(1, sizeof(t_shell));
	shell->tty = isatty(STDIN_FILENO);
	if (shell->tty)
		print_header();
	if (!shell)
		return (NULL);
	shell->enviro = NULL;
	init_env(&shell->enviro, envp);
	return (shell);
}

int	main(int argc, char **argv, char **envp)
{
	char	*mini;
	t_shell	*shell;
	int		ret;
	char	*line;

	(void)argc;
	(void)argv;
	shell = shell_crl(envp);
	manege_signal();
	//int i = 0;
	rl_catch_signals = 0;
	while (1)
	{
		shell->path = NULL;
		if (shell->tty)
			mini = readline("\001\033[38;5;205m\002minishell> \001\033[0m\002");
		else
		{
			line = get_next_line(STDIN_FILENO);
			//printf("line = |%s| ", line);
			mini = ft_strtrim(line, "\n");
			free(line);
		}

		if (!mini)
			break ;

		ret = check_readline(shell, mini);
		if (ret == 2)
			break ;

		if (ret == 1 || ft_structur(shell, mini) == 1)
			continue ;

		ft_pipex(shell);
		free_all(shell, mini);

	}
	free_shell(&shell);
	if (shell->tty)
		printf("Bye 👋\n");
}