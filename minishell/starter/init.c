/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponnusa <tponnusa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 11:21:38 by tponnusa          #+#    #+#             */
/*   Updated: 2024/02/02 13:18:21 by tponnusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_prompt_string(char *path)
{
	int	end;
	int	len;
	int	start;

	len = ft_strlen(path);
	start = 0;
	end = len;
	if (is_present(path, '/'))
	{
		if (path[len - 1] == '/')
		{
			end--;
			len--;
		}
	}
	while (len--)
	{
		if (path[len] == '/')
		{
			start = len + 1;
			break ;
		}
	}
	return (ft_substr(path, start, end - start));
}

char	*get_cwd_path(t_shell *shell_data)
{
	char	*cur_dir;

	cur_dir = (char *)malloc(PATH_MAX);
	if (cur_dir == NULL)
	{
		print_error(2);
		shell_data->status_code = EXIT_FAILURE;
		return (NULL);
	}
	if (getcwd(cur_dir, PATH_MAX) == NULL)
	{
		print_error(3);
		shell_data->status_code = EXIT_FAILURE;
		return (NULL);
	}
	return (cur_dir);
}

int	set_prompt(t_shell *data)
{
	char	*cur_dir;
	char	*tmp;

	cur_dir = get_cwd_path(data);
	if (cur_dir == NULL)
		return (1);
	tmp = get_prompt_string(cur_dir);
	free(cur_dir);
	if (tmp == NULL)
		return (1);
	data->prompt_str = ft_strjoin(tmp, " $ ");
	if (data->prompt_str == NULL)
		return (1);
	free(tmp);
	return (0);
}

int	init_shell_data(t_shell *shell_data, char **env)
{
	shell_data->env = NULL;
	shell_data->prompt_str = NULL;
	shell_data->status_code = 0;
	shell_data->command = NULL;
	shell_data->child_pid = NULL;
	shell_data->pipe_fd_in = STDIN_FILENO;
	if (set_prompt(shell_data))
	{
		shell_data->status_code = EXIT_FAILURE;
		return (print_error(2), 0);
	}
	shell_data->env = create_env_list(shell_data, env);
	init_signals();
	g_sig_interrupt = 0;
	return (1);
}

void	reset_struct(t_shell *shell_data)
{
	g_sig_interrupt = 0;
	shell_data->pipe_fd_in = STDIN_FILENO;
	if (shell_data->command)
		free_command(shell_data->command);
	if (shell_data->child_pid)
		free (shell_data->child_pid);
	shell_data->command = NULL;
	shell_data->child_pid = NULL;
}
