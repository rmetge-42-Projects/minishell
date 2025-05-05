/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemma <bemma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 11:02:57 by rmetge            #+#    #+#             */
/*   Updated: 2025/05/05 15:40:54 by bemma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	main(int argc, char **argv, char **envp)
// {
// 	t_shell *mini = malloc(sizeof(t_shell));
// 	// int i;

// 	mini->cmd = malloc(sizeof(t_cmd));
// 	// mini->cmd->path = ft_path(t_shell min);
// 	mini->env = envp;
// 	// char **path;
// 	(void)argc;
// 	// (void)argv;

// 	// path = ft_path(env);
// 	// char *cd = "ls cd  cat ";
// 	// ft_struc(path, "iubu uyi   8yg8gb ibbi '8yuguyv iuibi  uyuyvuygbuy' uyuyvuyg u");"Makefile""grep OBJ_DIR""wc -l""outfile"
// 	ft_pipex(mini);
// }

int main(int argc, char **argv, char **envp)
{
	t_shell	mini;
	t_cmd	*cmd1 = malloc(sizeof(t_cmd));
	t_cmd	*cmd2 = malloc(sizeof(t_cmd));
	(void)argv;
	(void)argc

	// Commande 1 : ls -l
	cmd1->com = malloc(sizeof(char *) * 3);
	cmd1->com[0] = strdup("ls");
	cmd1->com[1] = strdup("-l");
	cmd1->com[2] = NULL;
	cmd1->pipe = cmd2;

	// Commande 2 : grep ft
	cmd2->com = malloc(sizeof(char *) * 3);
	cmd2->com[0] = strdup("grep");
	cmd2->com[1] = strdup("ft");
	cmd2->com[2] = NULL;
	cmd2->pipe = NULL;

	mini.cmd = cmd1;
	mini.env = envp;

	ft_pipex(&mini);

	// Attendre tous les enfants
	while (wait(NULL) > 0);

	return (0);
}