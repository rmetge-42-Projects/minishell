/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemma <bemma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 11:02:57 by rmetge            #+#    #+#             */
/*   Updated: 2025/05/05 12:31:37 by bemma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	main(int argc, char **argv, char **env)
// {
// 	t_shell *mini = malloc(sizeof(t_shell));
// 	// int i;

// 	// mini->argv = malloc(sizeof(char *) * 5);
// 	// mini->argv[0] = argv[1];
// 	// mini->argv[1] = argv[2];
// 	// mini->argv[2] = argv[3];
// 	// mini->argv[3] = argv[4];
// 	// mini->argv[4] = NULL;
// 	// mini->cmd = malloc(sizeof(t_cmd));
// 	// // mini->cmd->path = ft_path(t_shell min);
// 	// mini->nv = env;
// 	// // char **path;
// 	// (void)argc;
// 	// // (void)argv;

// 	// // path = ft_path(env);
// 	// // char *cd = "ls cd  cat ";
// 	// // ft_struc(path, "iubu uyi   8yg8gb ibbi '8yuguyv iuibi  uyuyvuygbuy' uyuyvuyg u");"Makefile""grep OBJ_DIR""wc -l""outfile"
// 	// i = ft_pipex(mini);
//     char *line;
//     // char **args;
    
//     (void)argc;
//     (void)argv;

//     while (1)
//     {
//         line = readline("minishell$ ");
//         if (!line)
//             break;
//         add_history(line);
//         mini->argv = ft_split(line, ' '); // remplace par ton vrai split intelligent
//         if (fork() == 0)
//             execve(find_path(env, mini->argv[0]), mini->argv, env); // get_path() = à coder
//         else
//             wait(NULL);
//         free(line);
//         ft_f_s(mini->argv); // fonction pour free un char **
// 	}
// }


char *ft_strtok(char *str, const char *delim)
{
    static char *next = NULL;
    char *start;

    if (str)
        next = str;

    if (!next)
        return NULL;

    // Skip initial delimiters
    while (*next && strchr(delim, *next))
        next++;

    if (!*next)
        return NULL;

    start = next;

    // Find the end of the token
    while (*next && !strchr(delim, *next))
        next++;

    if (*next) {
        *next = '\0';
        next++;
    } else {
        next = NULL;
    }

    return start;
}


void execute_with_redirection(char *cmd, char **args, char *redirection_file, int is_append, char **envp)
{
    int file;
    
    // Ouvrir le fichier de redirection
    if (is_append)
        file = open(redirection_file, O_WRONLY | O_CREAT | O_APPEND, 0644); // pour >> (append)
    else
        file = open(redirection_file, O_WRONLY | O_CREAT | O_TRUNC, 0644); // pour > (overwrite)

    if (file == -1)
    {
        perror("Error opening file");
        return;
    }

    // Rediriger la sortie standard (stdout) vers le fichier
    if (dup2(file, STDOUT_FILENO) == -1)
    {
        perror("Error with dup2");
        close(file);
        return;
    }

    close(file);

    // Exécuter la commande
    if (execve(find_path(envp, cmd), args, NULL) == -1)
    {
        perror("Error executing command");
    }
}

int main(int argc, char **argv, char **envp)
{
    char *line;
    char **args;
    int is_append = 0;
    char *redirection_file = NULL;
	(void)argc;
	(void)argv;

    while (1)
    {
        line = readline("minishell$ ");
        if (!line)
            break;
        
        add_history(line);
        
        // Parser la ligne pour identifier les redirections
        if (strstr(line, ">"))
        {
            // Ici, on suppose que la redirection est " > filename"
            redirection_file = strtok(line, "> ");
            redirection_file = strtok(NULL, " "); // récupère le nom du fichier
            is_append = 0; // ">" indique que la redirection est de type écrasement
        }
        else if (strstr(line, ">>"))
        {
            // Ici, on suppose que la redirection est " >> filename"
            redirection_file = strtok(line, ">> ");
            redirection_file = strtok(NULL, " "); // récupère le nom du fichier
            is_append = 1; // ">>" indique un append
        }

        args = ft_split(line, ' '); // Assurez-vous que votre split ne coupe pas les redirections

        if (redirection_file)
            execute_with_redirection(args[0], args, redirection_file, is_append, envp);
        else
        {
            if (fork() == 0)
            {
                execve(find_path(envp, args[0]), args, envp);  // Exécution normale sans redirection
            }
            else
            {
                wait(NULL); // Attendre que l'enfant termine
            }
        }

        free(line);
        ft_f_s(args);
    }

    return 0;
}
