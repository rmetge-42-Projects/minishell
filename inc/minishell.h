/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemma <bemma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:49:15 by rmetge            #+#    #+#             */
/*   Updated: 2025/04/30 14:59:36 by bemma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>

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
	char	**path;
	char	**argv;
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
	char	*name;
	t_cmd	*cmd;
	t_list	*tokens;
	t_list	*env;
}	t_shell;

char	**ft_path(char **env);
int	ft_struc(char **path, char *cmd);
//char	**split_cmd(char *cmd);
// char	**ft_splitttt(char const *s);
void	*ft_free_split(char **split);
int		ft_pipex(t_cmd *com);

#endif