/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmetge <rmetge@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:49:15 by rmetge            #+#    #+#             */
/*   Updated: 2025/05/02 10:48:22 by rmetge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_cmd	t_cmd;

enum e_token
{
	ARG,
	QUOTE1,
	QUOTE2,
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

char			**ft_path(char **env);
int				ft_struc(char **path, char *cmd);
t_list			*ft_splitttt(char const *s);
t_token			*ft_tokennew(char *value, enum e_token type);
enum e_token	type(const char *s, int k);
int				chr_sep(char c);

#endif