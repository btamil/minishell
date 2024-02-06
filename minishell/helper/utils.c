/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabdul-k <fabdul-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 10:50:58 by tponnusa          #+#    #+#             */
/*   Updated: 2024/02/01 21:55:52 by fabdul-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_available_path(char *env_path, char *cmd)
{
	char	**paths;
	int		i;
	char	*valid_path;
	char	*tmp;

	i = 0;
	valid_path = NULL;
	tmp = NULL;
	if (access(cmd, F_OK) == 0)
		return (ft_strdup(cmd));
	paths = ft_split(env_path, ':');
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		valid_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(valid_path, F_OK) == 0)
		{
			free_array_of_string(paths);
			return (valid_path);
		}
		free(valid_path);
		i++;
	}
	return (free_array_of_string(paths), NULL);
}

int	is_number(char *s)
{
	int	i;

	i = 0;
	while ((s[i] >= 9 && s[i] <= 13) || (s[i] == 32))
		i++;
	if ((s[i] == '+' || s[i] == '-') && s[i + 1] != '\0')
		i++;
	while (s[i] && ft_isdigit(s[i]))
		i++;
	if (s[i] != '\0' && !ft_isdigit(s[i]))
		return (0);
	return (1);
}

int	check_special_sympols(char c)
{
	if (c == '<' || c == '>' || c == '[' || c == ']' || c == '='
		|| c == '\'' || c == '\"' || c == ',' || c == '.' || c == '?'
		|| c == ':' || c == '/' || c == '{' || c == '}' || c == '$'
		|| c == '^' || c == '%' || c == '#' || c == '@' || c == '*'
		|| c == '~' || c == '!' || c == '-' || c == '\\' || c == '+')
		return (1);
	return (0);
}

void	update_status(t_shell *data, int err_status)
{
	if (WIFEXITED(err_status))
		data->status_code = WEXITSTATUS(err_status);
	if (g_sig_interrupt == 1)
		data->status_code = SIGNAL_ERROR;
}

char	*get_env_path(t_shell *data)
{
	char	*env_path;

	env_path = get_env_value("PATH", &data->env);
	if (env_path == NULL)
	{
		ft_print_error(1, data);
		return (NULL);
	}
	return (env_path);
}
