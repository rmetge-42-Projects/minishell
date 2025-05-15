/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmetge <rmetge@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 11:02:57 by rmetge            #+#    #+#             */
/*   Updated: 2025/05/15 14:34:41 by rmetge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bultin(t_shell *shell)
{
	t_env	*current;

	if (ft_strncmp(shell->args[0], "export", 7) == 0)
	{
		ft_export(shell);
		return (1);
	}
	if (ft_strncmp(shell->args[0], "env", 4) == 0
		|| ft_strncmp(shell->args[0], "envp", 5) == 0)
	{
		current = *(shell->enviro);
		while (current)
		{
			if (current->value)
				printf("%s=%s\n", current->key, current->value);
			current = current->next;
		}
		return (1);
	}
	return (0);
}

int	check_readline(t_shell *shell, char *mini)
{
	volatile sig_atomic_t	g_sigint;

	g_sigint = 0;
	shell->line = mini;
	shell->args = ft_split(mini, ' ');
	if (g_sigint)
	{
		g_sigint = 0;
		return (1);
	}
	if (*mini)
		add_history(mini);
	if (!shell->args || !shell->args[0])
		return (free_all(shell, mini), 1);
	if (bultin(shell) == 1)
		return (free_all(shell, mini), 1);
	if (ft_exit(shell) == 1)
		return (free_all(shell, mini), 2);
	return (0);
}

t_shell	*shell_crl(char **envp)
{
	t_shell	*shell;

	print_header();
	shell = ft_calloc(1, sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->enviro = ft_calloc(1, sizeof(t_env *));
	init_env(shell->enviro, envp);
	shell->path = ft_path(envp);
	shell->env = envp;
	signal(SIGINT, ft_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	return (shell);
}

int	main(int argc, char **argv, char **envp)
{
	char	*mini;
	t_shell	*shell;
	int		ret;

	(void)argc;
	(void)argv;
	shell = shell_crl(envp);
	while (1)
	{
		mini = readline("\001\033[38;5;205m\002minishell> \001\033[0m\002");
		if (!mini)
			break ;
		ret = check_readline(shell, mini);
		if (ret == 1)
			continue ;
		else if (ret == 2)
			break ;
		if (ft_structur(shell, mini) == 1)
			continue ;
		ft_pipex(shell);
		free_all(shell, mini);
	}
	free_shell(&shell);
	printf("Bye 👋\n");
}
