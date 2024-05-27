/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinilla <gpinilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 23:48:22 by gpinilla          #+#    #+#             */
/*   Updated: 2024/04/23 19:42:27 by gpinilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <stdio.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdlib.h>
# include <dirent.h>
# include <fcntl.h>
# include <sys/types.h>
# include <signal.h>
# include <limits.h>
# include <termios.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <sys/param.h>
# include <readline.h>
# include <history.h>

long long int	g_status;

enum e_redir
{
	NONE = 0,
	IN = 1,
	OUT = 2,
	HEREDOC = 3,
	APPEND = 4
};

typedef struct s_inout
{
	int				type;
	char			*file;
	struct s_inout	*next;
}					t_inout;

typedef struct s_pipe
{
	int		fd[2];
	pid_t	*pid;
	int		og_fd[2];
}				t_pipe;

typedef struct s_env
{
	struct s_env	*prev;
	struct s_env	*next;
	char			*name;
	char			*value;
}					t_env;

typedef struct s_comand
{
	struct s_comand	*next;
	struct s_comand	*before;
	int				pipe_line;
	char			**arg;
	int				num_arg;
	t_inout			*redir;
	t_env			**env;
	char			**envp;
	char			*path;
}					t_comand;

typedef struct s_aux
{
	int				i;
	int				j;
	int				k;
	char			*name;
	char			*arg;
	char			*expand;
}					t_aux;

/*### BUILTINS ###*/

/*################## ft_cd.c #################*/
void		change_pwd(t_env *env, char *oldpwd);
int			aux_stat_ok(struct stat *stat_s, char *curr_dir);
int			cd_2arg(char **argv);
int			cd_home(char *oldpwd);
int			ft_cd(int argc, char **argv, t_env *env);

/*################## ft_echo.c #################*/
int			ft_check_n(char **argv, int *i);
int			ft_echo(int argc, char **argv);

/*################## ft_env.c #################*/
int			print_env(t_env *env);
int			ft_env(int argc, t_env *env);

/*################## ft_exit.c #################*/
int			ft_exit(t_comand **cmd, t_pipe **pipe_s);
char		*last_exit_status(void);

/*################## utils_builtins.c #################*/
int			ft_isspace(char c);
int			magic_atoi(char *nbr);
t_env		*create_new_env(t_comand *cmd, char **argv, int i);
int			cd_nodir(char *argv);
void		no_cwd(t_env *env);

/*################## ft_export.c #################*/
int			change_value(char *new, t_env *env_var);
t_env		*print_export(t_env *iter_env);
void		export_multiarg(t_comand *cmd, char **argv, int i, t_env *iter_env);
int			ft_export(t_comand *cmd, int argc, char **argv);
t_env		*check_if_exists(t_env *iter_env, char **argv, int i);

/*################## ft_pwd.c #################*/
int			ft_pwd(t_env *env);

/*################## ft_unset.c #################*/
t_env		*free_env(t_env **env);
int			delete_env_var(t_env **env);
int			ft_unset(t_comand *cmd, int argc, char **argv);

//################### get_cmds.c ##################
int			get_flag_redir(char *word, t_comand **cmds);
t_comand	*get_flag_pipe(t_comand **cmds, int *i, int *n_args);
int			get_args(char **words, t_comand *cmds, int *i, int *n_args);

//################### read.c ##################
t_comand	*get_line(t_env **env_list);
void		get_words(char *line, t_comand **cmds);
void		get_tokens(char **words, t_comand **cmds);
void		get_flags(char **words, t_comand **cmds, int *i, int *n_args);

/*################## redirs.c #################*/
int			set_redir(t_comand *cmd);
int			ft_in(t_inout *aux);
int			ft_out(t_inout *aux);
int			ft_heredoc(t_inout *aux);
int			ft_append(t_inout *aux);

/*################## inits.c #################*/
t_inout		*init_inout(t_comand **cmds);
void		init_cmd(t_comand *cmd);
t_comand	*newcmd(t_comand *old);
t_comand	*create_cmd(void);

/*### UTILS ###*/

/*################## utils_checks.c #################*/
int			check_empty_redir(t_comand *cmd);
int			check_only_space(char *s);
int			check_errors(t_comand *cmd);
int			check_empty_pipes(t_comand *cmd);

/*################## utils_env.c #################*/
int			valid_name(char c);
char		*get_pre_char(char *str, char c);
char		*get_post_char(char *str, char c);
int			shlvl_increaser(t_env *env_node, char **env, int *i);
char		**env_executor(t_env **env);

/*################## utils_env_2.c #################*/
char		*magic_ft_strjoin(char const *s1, char const *s2, char c);
int			count_nodes(t_env *env);

/*############## utils_executor_checks.c #############*/
int			check_builtin(char *command);
int			exec_builtin(t_comand *cmd, int result, t_pipe *pipe_s);
char		*check_cmds(char **split, char *arg);
char		**magic_split(char *env_value, char c, char *cmd);
char		*path_searcher(t_comand *cmd);

/*################## utils_executor.c #################*/
int			ft_wordlen(char *s, char c);
char		*ft_strndup(char *env_value, char *cmd, char c);
int			split_count_words(char *env_value, char c);
int			ft_free_arr(char **s, int i);
void		ft_tolower_str(char *str);

/*################## utils_executor_2.c #################*/
void		ft_close_fd(int *fd);
int			aux_check_path(t_comand *cmd, char *path);
int			is_file_dir(char *cmd);
void		exit_status(int *status);
char		**path_searcher_loop(char **split_path, t_env *iter_env,
				t_comand *cmd);

/*################## utils_expander.c #################*/
t_aux		*init_aux_struct(t_comand *cmd, int i);
int			reset_malloc(t_aux *aux, int malloc_len);
int			check_special_cases(t_comand *cmd, int i, char c, t_aux *aux);
void		swap_args(t_comand *cmd, int i, t_aux *aux);

/*################## utils_expander_2.c #################*/
char		*expand_var(char *str, char *value, char *name, t_aux *s_aux);
int			search_env_var(char **argv, t_aux *aux, t_env *env, int i);
void		save_and_expand(t_comand *cmd, int i, t_aux *aux);

//################## utils_redirs.c #################
int			remove_heredoc(t_comand *cmds);

//################## utils_quote.c #################
int			check_quote(char *line, int *leng);
int			check_redir(char *line, int *leng);
int			copy_quote(char *src, char *dest, int *i);
int			copy_quote_redir(char *src, char *dest, int *i, int *j);
int			copy_redir(char *src, char *dest, int *i);

/*################## utils_read.c #################*/
void		aux_leng_word(char *line, int *leng, int *space);
int			leng_word(char *line);
int			copy_word(char *dest, char *src, int *j);
void		count_args(char **words, t_comand *cmd);

/*################## utils_read_2.c #################*/
void		insert_env(t_comand *cmds, t_env **env_list);
void		count_word_loop(char *line, int *i, int *first_pos);
void		util_count_word(char *line, int *i);
int			count_word(char *line);

/*################## frees.c #################*/
void		free_redirs(t_comand **cmds);
void		free_cmds(t_comand **cmds);
void		reset_cmds(t_comand **cmds);
void		free_words(char ***words);
void		*free_aux_struc(t_aux **aux);

/*################## env_creation.c #################*/
t_env		*free_env_list(t_env *env);
t_env		*create_min_node(char *name, char *value, t_env *env);
t_env		*minimum_env(void);
t_env		*create_env_list(char **env);
t_env		*create_first_node(char *arg);

/*################## error_handler.c #################*/
int			ft_error(char *errmsg, int error);
void		ft_closefd(int *fd);
int			magic_ft_error(char *cmd, char *arg, char *errmsg, int error);

/*################## executor.c #################*/
int			check_executor(t_comand *cmd, t_pipe *pipe_s);
void		single_cmd(t_comand *cmd, t_pipe *pipe_s);
void		child_process(t_comand *cmd, t_pipe *pipe_s);
void		executor_loop(t_comand *cmd, t_pipe *pipe_s, int *n_process);
int			executor(t_comand *cmd, t_pipe *pipe_s);

/*################## expander.c #################*/
void		manage_single(t_aux *aux, char *str);
void		manage_double(t_aux *aux, char *str, t_comand *cmd, int i);
void		manager_expander(t_comand *cmd, t_aux *aux, int *i);
void		max_expander(t_comand *cmd, int len);
int			expander(t_comand *cmd);

/*################## redirs.c #################*/
int			redir_in(t_comand *cmd, char *ref);
int			redir_out(t_comand *cmd, char *ref, int type);
int			redir_heredoc(t_comand *cmd, int fd);

/*################## pipes.c #################*/
t_pipe		*init_pipe_s(t_comand *cmd);
void		set_dup2(t_pipe *pipe_s, int i);
void		free_pipe_s(t_pipe **pipe_s);

/*################## signals.c #################*/
void		wait_signal(int i);
void		safe_exit(t_env ***env);

/*################## set_heredoc.c #################*/
int			set_heredoc(t_comand *cmd, t_pipe *pipe_s);
int			create_heredoc(t_inout *aux, t_pipe *pipe_s);

#endif