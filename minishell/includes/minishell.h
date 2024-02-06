/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponnusa <tponnusa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 10:54:24 by tponnusa          #+#    #+#             */
/*   Updated: 2024/02/02 11:46:22 by tponnusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "expander.h"
# include "lexer.h"
# include "parser.h"
# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stddef.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

# define NOT_EXECUTED_STATUS 126
# define INCORRECT_CMD_USAGE 2
# define COMMAND_NOT_FOUND 127
# define EXIT_RANGE_ERROR 255
# define SIGNAL_ERROR 1

typedef struct s_command
{
	char				**args;
	int					num_redirection;
	struct s_lexer		*redirection;
	struct s_command	*next;
	char				*hd_file_name;
}	t_command;

typedef struct s_env_list
{
	char				*key;
	char				*value;
	struct s_env_list	*next;
}	t_env_list;

typedef struct s_shell
{
	t_env_list	*env;
	t_command	*command;
	char		*prompt_str;
	int			status_code;
	int			no_of_pipes;
	int			heredoc;
	int			*child_pid;
	int			pipe_fd_in;
}	t_shell;

int	g_sig_interrupt;

int				init_shell_data(t_shell *shell_data, char **env);
void			init_node(t_command **node);
void			init_signals(void);
int				check_quotes(char *input, t_shell *shell_data);

int				parser(t_lexer **list, t_shell *shell);
int				add_command_node(t_command **command, t_command *node);
void			delete_one_node(t_lexer **lst, int key);
int				handle_redirection(t_lexer **list, t_command **node,
					int num_red, t_shell *shell);

void			print_error(int i);
int				print_parse_error(int i, t_shell *shell, t_lexer **list);
void			print_error_exec(int i);
void			print_error2(int i, t_shell *data);

char			*get_cwd_path(t_shell *shell_data);
t_env_list		*create_env_list(t_shell *shell_data, char **env);
void			set_env_value(char *key, char *value, t_env_list **env_list);
char			*get_env_value(char *env_name, t_env_list **env_list);
void			delete_node(char *key, t_env_list **env_list);
void			add_to_list(char *new_key, char *new_value, t_shell *data);

int				execute_built_ins(t_shell *shell_data, char **cmds);
void			execute_built_in_main(t_shell *shell_data);
void			call_cd_execution(t_shell *shell_data, char **cmds);
void			print_env(int i, t_env_list **env_list);
void			print_export(t_env_list *itr);
void			call_echo(char **cmds, t_shell *data);
void			call_export(char **cmds, t_shell *shell_data);
void			call_unset(char **cmds, t_shell *shell_data);
void			call_exit(char **cmds, t_shell *shell_data);
void			exit_mini_shell(t_shell *data, int i);
int				is_built_in(char **cmds);

t_env_list		*create_list(void *key, void *val);
t_env_list		*get_last_node(t_env_list *lst);
void			list_add_back(t_env_list **lst, t_env_list *node);
int				is_key_present(t_env_list *list, char *new_key);
void			sort_list_ao(t_env_list **lst, int size);
int				ft_lstsize(t_env_list *lst);

void			execute_single_process(t_command *cmds, t_shell *shell_data);
void			execute_multiple_process(t_shell *shell_data, int fd[2]);
void			execute_command(t_shell *shell_data, char **cmds);
void			update_status(t_shell *data, int err_status);
void			ft_print_error(int i, t_shell *shell_data);
char			*get_env_path(t_shell *data);

void			create_heredoc(t_shell *data, t_command *cmd);
int				check_heredoc(t_lexer *redirs);
char			*create_hd_file(int i);
char			*get_file_name(char *file, t_shell *data,
					t_command *cmd, int i);
int				check_redirections(t_command *cmd);

int				is_present(char *s, char c);
int				ft_strcmp(char *s1, char *s2);
size_t			ft_strlen_2(char **s);
void			ft_strcpy(char *dst, const char *src);
int				get_char_count(char *s, char ch);
int				is_number(char *s);
int				check_special_sympols(char c);

char			*get_available_path(char *env_path, char *cmd);
char			**get_cmd_args_for_exec(char *path, char **cmds);
char			**get_all_env(t_env_list *env_list);

void			reset_struct(t_shell *shell_data);
void			free_command(t_command *com);
void			free_lexer_list(t_lexer *lex);
void			free_list(t_env_list *lst);
void			free_array_of_string(char **s);
void			close_all_pipe_fds(int fd_in, int pipe_in, int pipe_out);

t_command		*call_expander(t_shell *shell, t_command *cmd);
char			*handle_dollar(t_shell *shell, char *str);
char			*expander_str(t_shell *shell, char *str, int here_doc);
int				handle_question(t_shell *shell, char **tmp);
int				handle_eof(char *command_line);

#endif