/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemma <bemma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:49:15 by rmetge            #+#    #+#             */
/*   Updated: 2025/05/27 10:42:27 by bemma            ###   ########.fr       */
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
# include <sys/ioctl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <errno.h>

extern int	g_sig;

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

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_token
{
	char			*value;
	enum e_token	type;

}	t_token;

typedef struct s_cmd
{
	char			*path;
	char			**argv;
	t_list			*redirection;
	struct s_cmd	*pipe;
	int				last_heredoc_fd;

}	t_cmd;

typedef struct s_redir
{
	char			*file;
	enum e_redirect	type;
	int				heredoc_fd;
}	t_redir;

typedef struct s_shell
{
	t_cmd	*cmd;
	t_list	*tokens;
	char	*line;
	char	**args;
	char	**env;
	char	**path;
	t_env	*enviro;
	pid_t	*pids;
}	t_shell;

int				handle_heredoc(char *delimiter);
void			open_input(char *file);
int				open_out_put(char *file, int append, int last_fd);
void			error(char *message);
void			free_tokens(void *token);
void			free_redirec(void *redir);
void			ft_ctrl_c(int sig);
int				ft_exit(t_shell *shell);
void			ft_pipex(t_shell *shell);
char			*find_path(char **envp, char *cmd);
char			**ft_path(char **env);
int				ft_structur(t_shell *shell, char *cmd);
t_list			*stuctur_token(char const *s, t_shell *shell);
t_token			*ft_tokennew(char *value, enum e_token type);
enum e_token	token_type(const char *s);
int				chr_sep(char c);
char			*ft_find_path_cmd(char **path, char *argv);
int				stuctur_redicection(t_list **arg, t_cmd **cmd);
char			**str_arg(t_list *element);
t_cmd			*cmd_new(t_shell *shell);
void			arg_addback(t_list **argument, t_list **arg);
int				check_token(t_list *token);
t_token			*check_quote(t_shell *shell, int j, const char *s);
void			free_shell(t_shell **shell);
void			free_tokens(void *token);
void			free_cmd(t_cmd **cmd);
void			init_env(t_env **env, char **envp);
void			env_add_back(t_env **env, t_env *new_node);
void			ft_export(t_shell *shell);
void			print_header(void);
void			free_all(t_shell *shell, char *mini);
t_env			*env_new_node(char *key, char *value);
int				is_valid_identifier(char *key);
t_env			*copy_env_list(t_env *env);
void			ft_wait(int i, pid_t *pids);
void			manege_signal(void);
int				check_ctrl_h(void);
void			add_or_update_env(t_env **env, char *key, char *value);
void			ft_swap_env(t_env *current, t_env *next);
void			print_copy(t_env *cpy);
void			free_enviro(t_env **env);
char			**env(t_env	*enviro);
void			check_arg(t_shell *shell, char *value);
void			ft_process_quote(char const *s, int *j, char sep);
void			ft_ctrl_backslash(int sig);
int				len_dollar(char *arg);
char			*chr_path(char *arg, t_env *enviro);
void			ft_process_2(char const *s, int *j, int redir);
char			*ft_dollar(t_shell *shell, char *first, char *dest);
char			*space_join(char *s1, char *s2);
int				builtin(t_shell *shell);
int				ft_cd(t_shell *shell, char **argv);
int				has_output_redirection(t_cmd *cmd);

#endif