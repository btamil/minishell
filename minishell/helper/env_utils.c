/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabdul-k <fabdul-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 15:21:48 by tponnusa          #+#    #+#             */
/*   Updated: 2024/02/02 13:49:26 by fabdul-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env_list	*create_env_list(t_shell *shell_data, char **env)
{
	int			i;
	int			j;
	t_env_list	*tmp_node;
	t_env_list	**lst;

	i = 0;
	lst = &shell_data->env;
	while (env[i])
	{
		j = 0;
		while (env[i][j] != '=')
			j++;
		tmp_node = create_list(ft_substr(env[i], 0, j),
				ft_substr(env[i], j + 1, ft_strlen(env[i]) - j));
		if (tmp_node == NULL)
			return (NULL);
		list_add_back(lst, tmp_node);
		i++;
	}
	return (*lst);
}

char	*get_env_value(char *env_name, t_env_list **env_list)
{
	t_env_list	*itr;

	if (*env_list == NULL)
		return (0);
	itr = (*env_list);
	while (itr)
	{
		if (ft_strcmp(itr->key, env_name) == 0)
		{
			return (itr->value);
		}
		itr = itr->next;
	}
	return (NULL);
}

void	set_env_value(char *key, char *value, t_env_list **env_list)
{
	t_env_list	*itr;

	if (*env_list == NULL)
		return ;
	itr = (*env_list);
	while (itr)
	{
		if (ft_strcmp(itr->key, key) == 0)
		{
			free(itr->value);
			itr->value = value;
			break ;
		}
		itr = itr->next;
	}
}

void	print_env(int i, t_env_list **env_list)
{
	t_env_list	*itr;

	if (*env_list == NULL)
		return ;
	itr = (*env_list);
	if (i == 1)
		print_export(itr);
	else
	{
		while (itr)
		{
			if (itr->key && itr->value)
			{
				ft_putstr_fd(itr->key, 1);
				ft_putchar_fd('=', 1);
				ft_putendl_fd(itr->value, 1);
			}
			itr = itr->next;
		}
	}
}

void	delete_node(char *key, t_env_list **env_list)
{
	t_env_list	*current;
	t_env_list	*prev;

	current = (*env_list);
	if (current != NULL && ft_strcmp(current->key, key) == 0)
	{
		(*env_list) = current->next;
		free(current->key);
		free(current->value);
		free(current);
		return ;
	}
	while (current != NULL && ft_strcmp(current->key, key) != 0)
	{
		prev = current;
		current = current->next;
	}
	if (prev != NULL)
	{
		prev->next = current->next;
		free(current->key);
		free(current->value);
		free(current);
	}
}
