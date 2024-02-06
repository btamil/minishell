/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponnusa <tponnusa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 13:52:05 by tponnusa          #+#    #+#             */
/*   Updated: 2024/01/31 16:24:57 by tponnusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env_list	*swap(t_env_list *ptr1, t_env_list *ptr2)
{
	t_env_list	*tmp;

	tmp = ptr2->next;
	ptr2->next = ptr1;
	ptr1->next = tmp;
	return (ptr2);
}

int	ft_lstsize(t_env_list *lst)
{
	int	size;

	size = 0;
	while (lst != NULL)
	{
		lst = lst -> next;
		size++;
	}
	return (size);
}

void	sort_list_ao(t_env_list **lst, int size)
{
	t_env_list	**tmp;
	int			is_swap;
	int			i;
	int			j;

	i = 0;
	while (i < size)
	{
		tmp = lst;
		is_swap = 0;
		j = 0;
		while (j < size - i - 1)
		{
			if ((*tmp)->next && ft_strcmp((*tmp)->key, (*tmp)->next->key) > 0)
			{
				(*tmp) = swap((*tmp), (*tmp)->next);
				is_swap = 1;
			}
			tmp = &(*tmp)->next;
			j++;
		}
		if (is_swap == 0)
			break ;
		i++;
	}
}
