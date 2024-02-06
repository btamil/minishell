/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponnusa <tponnusa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 15:54:51 by tponnusa          #+#    #+#             */
/*   Updated: 2024/01/31 15:54:51 by tponnusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_free_array(char **s, int i)
{
	while (i >= 0)
	{
		if (s[i] != NULL)
			free(s[i]);
		i--;
	}
	free(s);
}

char	**get_cmd_args_for_exec(char *path, char **cmds)
{
	char	**new_args;
	int		len;
	int		i;

	len = ft_strlen_2(cmds);
	new_args = (char **)malloc(sizeof(char *) * (len + 2));
	if (new_args == NULL)
		return (NULL);
	i = 0;
	new_args[0] = (char *)malloc(sizeof(char) * (ft_strlen(path) + 1));
	if (new_args[0] == NULL)
		return (NULL);
	ft_strcpy(new_args[0], path);
	i++;
	while (i < len && cmds && cmds[i])
	{
		new_args[i] = (char *)malloc(sizeof(char) * (ft_strlen(cmds[i]) + 1));
		if (new_args[i] == NULL)
			return (ft_free_array(new_args, i), NULL);
		ft_strcpy(new_args[i], cmds[i]);
		i++;
	}
	new_args[i] = 0;
	return (new_args);
}

char	**allocate_arrayofarray(t_env_list *env_list)
{
	char		**env_arr;
	t_env_list	*tmp;
	int			rows;
	int			cols;
	int			i;

	rows = ft_lstsize(env_list);
	tmp = env_list;
	i = 0;
	env_arr = (char **)malloc((rows + 1) * sizeof(char *));
	if (env_arr == NULL)
		return (NULL);
	while (i < rows && tmp)
	{
		cols = ft_strlen(tmp->key) + ft_strlen(tmp->value);
		env_arr[i] = (char *)malloc((cols + 2) * sizeof(char *));
		if (env_arr[i] == NULL)
		{
			ft_free_array(env_arr, i);
			return (NULL);
		}
		i++;
		tmp = tmp -> next;
	}
	return (env_arr);
}

char	*get_env_string(char *key, char *val)
{
	char	*tmp;
	char	*tmp1;

	tmp = ft_strjoin(key, "=");
	tmp1 = ft_strjoin(tmp, val);
	free(tmp);
	return (tmp1);
}

char	**get_all_env(t_env_list *env_list)
{
	char		**env_arr;
	int			i;
	t_env_list	*tmp;
	char		*tmp_str;

	i = 0;
	tmp_str = NULL;
	tmp = env_list;
	env_arr = allocate_arrayofarray(env_list);
	if (env_arr == NULL)
		return (NULL);
	i = 0;
	tmp = env_list;
	while (tmp)
	{
		tmp_str = get_env_string(tmp->key, tmp->value);
		if (!tmp_str)
			break ;
		ft_strlcpy(env_arr[i], tmp_str, ft_strlen(tmp_str) + 1);
		free(tmp_str);
		tmp = tmp -> next;
		i++;
	}
	env_arr[i] = 0;
	return (env_arr);
}
