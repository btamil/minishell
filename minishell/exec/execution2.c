/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabdul-k <fabdul-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 14:38:54 by tponnusa          #+#    #+#             */
/*   Updated: 2024/02/02 16:24:28 by fabdul-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_child_process(int fd[2], t_shell *data, int i, t_command *cmd)
{
	if (i > 0 && dup2(data->pipe_fd_in, STDIN_FILENO) < 0)
		return (print_error_exec(19));
	close(fd[0]);
	if (cmd->next && dup2(fd[1], 1) < 0)
		return (print_error_exec(19));
	close(fd[1]);
	if (i > 0 && data->pipe_fd_in >= 0)
		close(data->pipe_fd_in);
	if (cmd->redirection && check_redirections(cmd))
		exit_mini_shell(data, 1);
	if (cmd && is_built_in(cmd->args))
	{
		if (cmd && ft_strcmp(cmd->args[0], "exit") == 0)
			exit_mini_shell(data, 0);
		execute_built_ins(data, cmd->args);
		exit_mini_shell(data, 1);
	}
	else if (cmd && cmd->args[0])
		execute_command(data, cmd->args);
	exit_mini_shell(data, 1);
}

int	get_redirection_fd_in(t_command *cmd, int cur_fd_in)
{
	int		fd_in;
	t_lexer	*redirs;
	t_lexer	*redir_to_read;

	redirs = cmd -> redirection;
	redir_to_read = NULL;
	fd_in = cur_fd_in;
	while (redirs)
	{
		if ((redirs ->token == LESS || redirs ->token == LESS_LESS)
			&& redirs -> next == NULL)
			redir_to_read = redirs;
		redirs = redirs -> next;
	}
	if (redir_to_read && redir_to_read->token == LESS_LESS && cur_fd_in >= 0)
	{
		close(cur_fd_in);
		fd_in = open(cmd->hd_file_name, O_RDONLY);
	}
	else if (redir_to_read && redir_to_read ->token == LESS)
		fd_in = open(redir_to_read ->word, O_RDONLY);
	if (fd_in < 0)
		return (cur_fd_in);
	return (fd_in);
}

int	wait_process_to_finish(int tot, int *child_pid, t_shell *data, int *fd[2])
{
	int	i;
	int	err_status;

	i = 0;
	err_status = 0;
	while (i < tot)
	{
		waitpid(child_pid[i], &err_status, 0);
		i++;
	}
	if (WIFEXITED(err_status))
	{
		data->status_code = WEXITSTATUS(err_status);
		close_all_pipe_fds(data->pipe_fd_in, (*fd)[0], (*fd)[1]);
	}
	return (EXIT_SUCCESS);
}

t_command	*before_execute(t_shell *data, t_command *cmd)
{
	t_command	*cmd_expand;

	cmd_expand = call_expander(data, cmd);
	create_heredoc(data, cmd);
	return (cmd_expand);
}

void	execute_multiple_process(t_shell *data, int fd[2])
{
	int			i;
	t_command	*tmp;

	i = 0;
	tmp = data->command;
	while (tmp)
	{
		tmp = before_execute(data, tmp);
		if (tmp->next && pipe(fd) < 0)
			return (print_error_exec(16));
		data->child_pid[i] = fork();
		if (data->child_pid[i] < 0)
			return (print_error(4));
		if (data->child_pid[i] == 0)
			execute_child_process(fd, data, i, tmp);
		close(fd[1]);
		if (i != 0 && data->pipe_fd_in >= 0)
			close(data->pipe_fd_in);
		data->pipe_fd_in = get_redirection_fd_in(tmp, fd[0]);
		tmp = tmp->next;
		i++;
	}
	wait_process_to_finish(i, data->child_pid, data, &fd);
	close_all_pipe_fds(data->pipe_fd_in, fd[0], fd[1]);
}
