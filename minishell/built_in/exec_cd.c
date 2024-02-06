/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponnusa <tponnusa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:52:02 by tponnusa          #+#    #+#             */
/*   Updated: 2024/01/31 18:24:11 by tponnusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	validate_cd_input(char *dir_name)
{
	if (access(dir_name, F_OK) == 0)
	{
		print_error(8);
		return (EXIT_FAILURE);
	}
	else if (get_available_path("PATH", dir_name) == NULL)
	{
		print_error(9);
		return (EXIT_FAILURE);
	}
	return (0);
}

int	set_path_to_home(t_env_list **lst, t_shell *data)
{
	char	*new_dir_path;

	new_dir_path = get_env_value("HOME", lst);
	if (new_dir_path == NULL)
	{
		print_error(6);
		data->status_code = EXIT_FAILURE;
		return (EXIT_FAILURE);
	}
	else if (chdir(new_dir_path) < 0)
	{
		print_error(7);
		data->status_code = EXIT_FAILURE;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	change_env(t_shell *shell_data, char *cmd)
{
	char	*tmp_pwd;
	char	*tmp_path;

	tmp_pwd = NULL;
	tmp_path = NULL;
	tmp_pwd = get_env_value("PWD", &shell_data->env);
	if (tmp_pwd != NULL)
		add_to_list(ft_strdup("OLDPWD"), ft_strdup(tmp_pwd), shell_data);
	if (cmd && get_char_count(cmd, '/') == 2)
		set_env_value("PWD", ft_strdup("//"), &shell_data->env);
	else
	{
		tmp_path = get_cwd_path(shell_data);
		if (tmp_path != NULL)
		{
			set_env_value("PWD", tmp_path, &shell_data->env);
			shell_data->status_code = EXIT_SUCCESS;
		}
		else
			shell_data->status_code = EXIT_FAILURE;
	}
}

void	call_cd_execution(t_shell *shell_data, char **cmds)
{
	if (ft_strlen_2(cmds) > 2)
	{
		shell_data->status_code = EXIT_FAILURE;
		print_error(10);
		return ;
	}
	if (ft_strlen_2(cmds) == 1 || (cmds[1] && (ft_strcmp(cmds[1], "~") == 0)))
	{
		set_path_to_home(&(shell_data->env), shell_data);
		if (!shell_data->status_code)
			change_env(shell_data, cmds[1]);
		return ;
	}
	if (chdir(cmds[1]) < 0)
	{
		shell_data->status_code = validate_cd_input(cmds[1]);
		return ;
	}
	else
	{
		change_env(shell_data, cmds[1]);
	}
}
