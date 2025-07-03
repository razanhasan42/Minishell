/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhasan <rhasan@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:07:39 by rhasan            #+#    #+#             */
/*   Updated: 2025/06/22 13:07:49 by rhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <curses.h>
# include <dirent.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

extern int					g_signal_status;
typedef enum e_token_type
{
	REDIR_INPUT,
	REDIR_OUTPUT,
	REDIR_APPEND,
	REDIR_HEREDOC,
	TOKEN_PIPE,
	WORD
}							t_token_type;

typedef struct s_redirection
{
	t_token_type			type;
	char					*filename;
	char					*limiter;
	struct s_redirection	*next;
	int						is_quoted_limiter;
	int						heredoc_fd;

}							t_redirection;

typedef struct tokenizer
{
	char					*tmp;
	int						j;
}							t_add_to_node;

typedef struct s_env
{
	char					*name;
	char					*value;
	struct s_env			*next;
}							t_env;

typedef struct s_node
{
	char					*value;
	struct s_node			*next;
	t_token_type			type;

}							t_node;

typedef struct s_command
{
	char					**argv;
	t_node					*tokens;
	struct s_command		*next;
	t_redirection			*redir_list;
	t_token_type			type;
	int						input_fd;
	int						is_invalid;

}							t_command;

typedef struct s_expansion_state
{
	int						i;
	int						in_double_quote;
	int						in_single_quote;
}							t_expansion_state;

typedef struct s_shell_context
{
	char					*program_name;
	int						last_exit_status;
}							t_shell_context;

typedef struct s_pipe_vars
{
	t_command				*head;
	t_command				*tail;
	t_node					*start;
	t_node					*curr;
	t_node					*prev;
}							t_pipe_vars;

typedef struct s_exec_fds
{
	int						prev_fd;
	int						pipe_fd[2];
}							t_exec_fds;

typedef struct s_expand_context
{
	t_expansion_state		*state;
	t_shell_context			*context;
	t_env					*env_list;
}							t_expand_context;

typedef struct s_tokenize_params
{
	char					*command;
	t_node					**linked_list;
	t_shell_context			*context;
	t_env					**env_list;
	t_command				**cmd_list;
	int						*heredoc_cancelled;
}							t_tokenize_params;

typedef struct s_exec_cleanup_params
{
	char					*command;
	t_node					*linked_list;
	t_command				*cmd_list;
	t_env					**env_list;
	int						heredoc_fd;
	t_exec_fds				*fds;
}							t_exec_cleanup_params;

typedef struct s_exec_context
{
	char					**argv;
	char					**envp;
	char					*cmd_path;
	t_node					**tokens;
	t_command				*cmd;
	t_env					*env;
	t_env					**env_list;
}							t_exec_context;

typedef struct s_process_context
{
	t_node					**node;
	t_add_to_node			*n;
	char					in_quote;
	char					*cmd;
	int						*i;
}							t_process_context;

typedef struct s_heredoc_state
{
	int						*heredoc_fd;
	int						*heredoc_cancelled;
}							t_heredoc_state;

typedef struct s_heredoc_params
{
	t_env				*env_list;
	t_shell_context		*context;
	t_command			*cmd;
	t_heredoc_state		*state;

}					t_heredoc_params;
int							handle_token_addition(t_node **node,
								t_add_to_node *n);
int							builtin_expr(char **argv);
t_add_to_node				*init_tmp(const char *cmd);
void						update_quote(char c, char *in_quote);
int							handle_operator_chars(t_node **node, char *cmd,
								int *i, t_add_to_node *n);
int							parse_cmd(t_node **node, char *cmd,
								t_add_to_node *n);
t_env						*create_env_list(char **envp);
t_command					*split_commands_by_pipe(t_node *tokens);
t_command					*create_command_node(t_node *start, t_node *end);
t_redirection				*create_redirection(t_token_type type,
								char *filename);
void						unset_env_variable(t_env **env, const char *name);
void						set_env_value_exec(t_env **env_ptr,
								const char *name,
								const char *value);
void						remove_redirection_tokens(t_node **tokens);
void						free_token_node(t_node *node);
void						sort_env_list(t_env **env_list);
void						swap_env_vars(t_env *a, t_env *b);
void						add_env_variable(t_env **env_list, char *name,
								char *value);
void						handle_env(t_env *env_list);
void						expand_variable(t_node **linked_list,
								t_shell_context *context,
								t_env *env_list);
void						free_env_list(t_env *env_list);
void						init_pipe_split_vars(t_pipe_vars *vars,
								t_node *tokens);
void						signal_child_heredoc(void);
void						signal_parent_heredoc(void);
void						add_node_to_list(t_node **head, char *token);
void						free_list(t_node **node);
void						build_command_argv(t_command *cmd);
void						mark_pipe_tokens(t_node *tokens);
void						rm_quote(t_node **node);
void						handle_filename(t_node *curr, char *filename,
								t_redirection **redir_list);
void						assign_redir_type(t_node *curr);
int							apply_redirections(t_redirection *redir_list,
								t_exec_fds *fds);
void						free_redirections(t_redirection **redir);
void						init_signal(void);
void						free_split(char **arr);
void						free_envp(char **envp);
void						free_argv(char **argv);
char						*expand_var_in_string(char *original,
								t_expansion_state *state,
								t_shell_context *context,
								t_env *env_list);
int							is_exit_command(t_command *cmd);
char						**convert_tokens_to_argv_exec(t_node *tokens);
char						**convert_tokens_to_argv(t_node *tokens);
char						*find_in_path(char *cmd, t_env *env);
char						*get_env_value(t_env *env_list, char *var_name);
char						*get_variable_value(char *str,
								t_expansion_state *state,
								t_env *env_list);
char						*get_expanded_value(t_env *env_list, char *value,
								t_shell_context *context,
								t_expansion_state *state);
char						*build_expanded_string(char *original,
								t_expansion_state *state,
								t_shell_context *context,
								t_env *env_list);
char						*append_char_to_expanded(char *expanded, char c);
char						*expand_line_with_vars(char *line, t_env *env_list);
char						*append_env_var(const char *line, int *i,
								t_env *env_list, char *result);
char						*strip_quotes(char *value);
char						**env_to_envp(t_env *env);
int							read_and_validate_command(char **command,
								t_shell_context *context);
int							execute_pipeline_main(t_command *cmd_list,
								t_env **env_list,
								int exit_status, t_exec_fds *fds);
int							tokenize_and_prepare(t_tokenize_params *params);
int							tokenize_and_build_commands(
								t_tokenize_params *params);
int							builtin_env(t_env *env);
int							builtin_unset(char **argv, t_env **env);
int							builtin_export(char **argv, t_env **env);
int							builtin_echo(char **argv);
int							builtin_exit(char **argv, t_env *env_list,
								t_command *cmd_list, int last_status);
int							builtin_cd(char **argv, t_env **env);
int							builtin_pwd(void);
int							export_assignment(char *arg, t_env **env);
int							export_list(t_env *env);
int							exec_builtin_cmd(t_command *cmd, t_env **env,
								int exit_status);
int							is_builtin(t_command *cmd);
int							excute(t_command *cmd_list, t_env *env);
int							check_quote(char *str, int i, int *in_double_quote,
								int *in_single_quote);
int							count_words(t_node *tokens);
int							check_quotes(const char *str);
int							parse_redirection(t_node *linked_list,
								t_redirection **redir_list);
int							build_commands_main(t_command *cmd_list);
int							split_into_tokens(t_node **node, char *cmd);
int							count_qoutes(char *cmd);
int							handling_error(t_node *curr);
bool						process_pipe_segment(t_pipe_vars *vars);
bool						add_command_node_safe(t_pipe_vars *vars,
								t_node *start,
								t_node *end);
bool						is_redirection(char *value);
void						free_command_list(t_command *cmd_list);
void						assign_token_types(t_node *tokens);
void						handle_heredoc_child(t_redirection *hd,
								t_heredoc_params *params,
								int *pipe_fd, t_command *cmd_list);
int							parse_heredocs(t_tokenize_params *params,
								t_command *cmd);
void						append_redir(t_redirection *list,
								t_redirection *new_redir);
void						cleanup_and_exit(t_exec_context *ctx,
								int exit_code);
void						setup_child_process(t_command *old_cmd,
								t_command *cmd,
								t_exec_fds *fds,
								t_env *env);
void						handle_parent_cleanup(t_exec_fds *fds,
								t_command *cmd);
void						exec_command(t_node *tokens, t_env *env,
								t_command *old_cmd, t_command *cmd_list);
int							allocate_argv(t_command *cmd, int count);
int							has_non_redirection_token(t_node *tok);
int							fill_argv(t_command *cmd, int count);
t_node						*skip_non_word_tokens(t_node *curr);
t_node						*skip_if_redirection(t_node *node);
int							process_word_token(t_command *cmd, t_node *curr,
								int *i);
int							builtin_expr(char **argv);
void						execute_and_cleanup(t_exec_cleanup_params *params,
								t_shell_context *context,
								int *heredoc_cancelled);
t_redirection				*new_redirection(t_token_type type,
								const char *limiter);
int							handle_heredoc_final(t_redirection *hd,
								t_heredoc_state *state);
int							handle_heredoc_allocation_failure(
								t_heredoc_state *state);
int							process_heredoc(t_redirection *hd,
								t_heredoc_params *params,
								t_command *cmd_list);
void						init_heredoc_limiter(t_redirection *hd, char *lim);
void						handle_heredoc_parent(pid_t pid, int *pipe_fd,
								t_heredoc_state *state,
								t_shell_context *context);
pid_t						handle_child_and_fork(t_exec_fds *fds,
								t_command *cmd_list,
								t_command *cmd, t_env *env);
int							get_exit_status(int status);
t_env						*create_env_node(char *key, char *value);
void						safe_close(int fd);
void						cleanup_and_exit_hd(t_redirection *hd,
								t_heredoc_params *params,
								int exit_code,	int *pipe_fd);
void						print_split_result(t_node *head);
#endif
