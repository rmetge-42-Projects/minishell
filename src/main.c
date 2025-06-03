/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmetge <rmetge@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 11:02:57 by rmetge            #+#    #+#             */
/*   Updated: 2025/06/03 13:12:50 by rmetge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig;

int	check_readline(t_shell *shell, char *mini)
{
	shell->line = mini;
	shell->args = ft_split(mini, ' ');
	if (*mini)
		add_history(mini);
	if (!shell->args || !shell->args[0])
		return (1);
	return (0);
}

void	shlvl(t_env *enviro)
{
	t_env	*tmp;
	int		val;

	tmp = enviro;
	while (ft_strcmp(tmp->key, "SHLVL") != 0)
		tmp = tmp->next;
	if (ft_strcmp(tmp->key, "SHLVL") == 0)
	{
		val = ft_atoi(tmp->value);
		free(tmp->value);
		tmp->value = ft_itoa(val + 1);
	}
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
	shlvl(shell->enviro);
	return (shell);
}

char	*read_line(t_shell *shell, char *mini)
{
	char	*line;

	if (shell->tty)
		mini = readline("\001\033[38;5;205m\002minishell> \001\033[0m\002");
	else
	{
		line = get_next_line(STDIN_FILENO);
		mini = ft_strtrim(line, "\n");
		free(line);
	}
	if (!mini)
	{
		if (shell->tty)
			ft_putendl_fd("exit", STDERR_FILENO);
		exit_shell(shell, shell->exit_code, 0);
	}
	return (mini);
}

int	main(int argc, char **argv, char **envp)
{
	char	*mini;
	t_shell	*shell;
	int		ret;

	(void)argc;
	(void)argv;
	shell = shell_crl(envp);
	manege_signal();
	rl_catch_signals = 0;
	mini = NULL;
	while (1)
	{
		shell->path = NULL;
		mini = read_line(shell, mini);
		ret = check_readline(shell, mini);
		if (ret == 1 || ft_structur(shell, mini) == 1)
			continue ;
		ft_pipex(shell);
		free_all(shell, mini);
	}
}
