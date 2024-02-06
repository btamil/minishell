/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponnusa <tponnusa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 19:44:14 by tponnusa          #+#    #+#             */
/*   Updated: 2024/01/29 19:44:14 by tponnusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_print_error(int i, t_shell *shell_data)
{
	if (!shell_data)
		return ;
	if (i == 1)
	{
		shell_data->status_code = EXIT_FAILURE;
		print_error_exec(10);
	}
	else if (i == 2)
	{
		shell_data->status_code = COMMAND_NOT_FOUND;
		print_error_exec(17);
	}
}

void	free_exec_parameters(char *path, char **args, char **env)
{
	free(path);
	free_array_of_string(args);
	free_array_of_string(env);
}

void	execute_command(t_shell *shell_data, char **cmds)
{
	char	*tmp_path;
	char	**env;
	char	**cmd_args;

	env = NULL;
	cmd_args = NULL;
	tmp_path = NULL;
	if (get_env_path(shell_data) == NULL)
		return ;
	if (cmds[0] && cmds[0][0] != '\0')
		tmp_path = get_available_path(get_env_path(shell_data), cmds[0]);
	if (tmp_path != NULL)
	{
		cmd_args = get_cmd_args_for_exec(tmp_path, cmds);
		env = get_all_env(shell_data->env);
		if (env && cmd_args && (execve(tmp_path, cmd_args, env) == -1))
		{
			shell_data->status_code = NOT_EXECUTED_STATUS;
			print_error_exec(11);
			free_exec_parameters(tmp_path, cmd_args, env);
		}
	}
	else
		ft_print_error(2, shell_data);
	exit_mini_shell(shell_data, 1);
}

void	execute_in_child(t_shell *data, t_command *cmd)
{
	if (check_redirections(cmd))
	{
		data->status_code = EXIT_FAILURE;
		exit_mini_shell(data, 1);
	}
	if (cmd->args && cmd->args[0] && is_built_in(cmd->args))
	{
		execute_built_in_main(data);
		exit_mini_shell(data, 1);
	}
	else if (cmd->args && cmd->args[0])
	{
		execute_command(data, cmd->args);
	}
	exit_mini_shell(data, 0);
}

void	execute_single_process(t_command *cmd, t_shell *data)
{
	int	child_pid;
	int	err_status;
	int	exit_flag;

	child_pid = 0;
	err_status = 0;
	exit_flag = 0;
	if ((cmd->args[0] && ((is_built_in(cmd->args) && !cmd->redirection)
				|| (data->heredoc && (ft_strcmp(cmd->args[0], "exit") == 0)))))
		execute_built_in_main(data);
	else
	{
		if (cmd->args[0] && ft_strcmp(cmd->args[0], "exit") == 0)
			exit_flag = 1;
		child_pid = fork();
		if (child_pid < 0)
			return (print_error(4));
		if (child_pid == 0)
			execute_in_child(data, cmd);
		waitpid(child_pid, &err_status, 0);
		update_status(data, err_status);
		if (exit_flag)
			exit_mini_shell(data, 1);
	}
}
