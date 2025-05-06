/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemma <bemma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 11:02:57 by rmetge            #+#    #+#             */
/*   Updated: 2025/05/06 16:36:06 by bemma            ###   ########.fr       */
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

// int main(int argc, char **argv, char **envp)
// {
// 	t_shell	mini;
// 	t_cmd	*cmd1 = malloc(sizeof(t_cmd));
// 	t_cmd	*cmd2 = malloc(sizeof(t_cmd));
// 	t_cmd	*cmd3 = malloc(sizeof(t_cmd));
// 	(void)argv;
// 	(void)argc;

// 	// Commande 1 : ls -l
// 	// cmd1->com = malloc(sizeof(char *) * 3);
// 	// cmd1->com[0] = "ls";
// 	// cmd1->com[1] = "-l";
// 	// cmd1->com[2] = NULL;
// 	// cmd1->pipe = cmd2;

// 	// // Commande 2 : grep ft
// 	// cmd2->com = malloc(sizeof(char *) * 3);
// 	// cmd2->com[0] = "grep";
// 	// cmd2->com[1] = "o";
// 	// cmd2->com[2] = NULL;
// 	// cmd2->pipe = cmd3;

// 	// cmd3->com = malloc(sizeof(char *) * 3);
// 	// cmd3->com[0] = "echo";
// 	// cmd3->com[1] = "bonjour";
// 	// cmd3->com[2] = NULL;
// 	// cmd3->pipe = NULL;

// 	cmd1->com = malloc(sizeof(char *) * 3);
// 	cmd1->com[0] = "cat";
// 	cmd1->com[1] = NULL;
// 	cmd1->pipe = cmd2;

// 	// Commande 2 : grep ft
// 	cmd2->com = malloc(sizeof(char *) * 3);
// 	cmd2->com[0] = "cat";
// 	cmd2->com[1] = NULL;
// 	cmd2->pipe = cmd3;

// 	cmd3->com = malloc(sizeof(char *) * 3);
// 	cmd3->com[0] = "ls";
// 	cmd3->com[1] = NULL;
// 	cmd3->pipe = NULL;

// 	t_redir *r1 = malloc(sizeof(t_redir));
// 	r1->type = INPUT;
// 	r1->file = "input.txt");

// 	t_redir *r2 = malloc(sizeof(t_redir));
// 	r2->type = OUTPUT;
// 	r2->file = "output.txt";

// 	t_list *redir1 = ft_lstnew(r1);
// 	t_list *redir2 = ft_lstnew(r2);
// 	redir1->next = redir2;

// 	cmd1->redirection = redir1;


// 	mini.cmd = cmd1;
// 	mini.env = envp;

// 	ft_pipex(&mini);

// 	// Attendre tous les enfants
// 	while (wait(NULL) > 0);

// 	return (0);
// }

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
	char *line;
	char **args;
	char *path;

	(void)argc;
	(void)argv;
	print_header();
	while (1)
	{
		line = readline("\033[38;5;205mminishell> \033[0m");
		if (!line)
			break;
		if (*line)
			add_history(line);
		args = ft_split(line, ' ');

		if (!args || !args[0])
		{
			free(line);
			ft_f_s(args);
			continue;
		}

		// 📦 Gestion du built-in "exit"
		if (strcmp(args[0], "exit") == 0)
		{
			free(line);
			ft_f_s(args);
			break;
		}

		path = find_path(envp, args[0]);
		if (!path)
		{
			fprintf(stderr, "minishell: command not found: %s\n", args[0]);
		}
		else
		{
			pid_t pid = fork();
			if (pid == 0)
			{
				execve(path, args, envp);
				perror("execve");
				exit(1);
			}
			else
			{
				wait(NULL);
			}
			free(path);
		}

		free(line);
		ft_f_s(args);
	}

	printf("Bye 👋\n");
	return 0;
}
