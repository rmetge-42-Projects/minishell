/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemma <bemma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:49:15 by rmetge            #+#    #+#             */
/*   Updated: 2025/05/05 15:36:17 by bemma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stddef.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>


typedef struct s_cmd	t_cmd;

enum e_token
{
	ARG,
	PIPE,
	REDIRECT
};

enum e_redirect
{
	HEREDOC,
	APPEND,
	INPUT,
	OUTPUT
};

typedef struct s_token
{
	char			*value;
	enum e_token	type;
}	t_token;

typedef struct s_cmd
{
	char	*path;
	char	**com;
	t_list	*redirection;
	t_cmd	*pipe;

}	t_cmd;

typedef struct s_redir
{
	char			*file;
	enum e_redirect	type;
}	t_redir;

typedef struct s_shell
{
	char	**line;
	t_cmd	*cmd;
	t_list	*tokens;
	char	**env;
	int		nb_pipe;
}	t_shell;

// char	**ft_path(char **env);
char	*find_path(char **envp, char *cmd);
int	ft_struc(char **path, char *cmd);
//char	**split_cmd(char *cmd);
// char	**ft_splitttt(char const *s);
void	*ft_f_s(char **split);
void	ft_pipex(t_shell *mini);

#endif