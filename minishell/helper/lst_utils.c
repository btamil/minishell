/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponnusa <tponnusa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 13:47:26 by tponnusa          #+#    #+#             */
/*   Updated: 2024/01/28 19:09:02 by tponnusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env_list	*create_list(void *key, void *val)
{
	t_env_list	*node;

	node = (t_env_list *)malloc(sizeof(t_env_list));
	if (!node || !key)
		return (NULL);
	node -> key = key;
	node -> value = val;
	node -> next = NULL;
	return (node);
}

t_env_list	*get_last_node(t_env_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst -> next;
	return (lst);
}

void	list_add_back(t_env_list **lst, t_env_list *node)
{
	t_env_list	*tmp;

	if (*lst == NULL)
	{
		*lst = node;
		return ;
	}
	tmp = get_last_node(*lst);
	tmp -> next = node;
}

int	is_key_present(t_env_list *list, char *new_key)
{
	t_env_list	*itr;

	itr = list;
	while (itr)
	{
		if (ft_strcmp(itr->key, new_key) == 0)
		{
			return (1);
		}
		itr = itr -> next;
	}
	return (0);
}

void	add_to_list(char *new_key, char *new_value, t_shell *data)
{
	t_env_list	**lst;
	t_env_list	*new_node;

	new_node = NULL;
	lst = &data -> env;
	if (is_key_present(*lst, new_key))
	{
		set_env_value(new_key, new_value, lst);
		free(new_key);
		return ;
	}
	new_node = create_list(new_key, new_value);
	if (new_node == NULL)
	{
		data ->status_code = EXIT_FAILURE;
		print_error(2);
		return ;
	}
	list_add_back(lst, new_node);
}
