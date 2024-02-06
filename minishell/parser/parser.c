/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabdul-k <fabdul-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 08:19:47 by fabdul-k          #+#    #+#             */
/*   Updated: 2024/01/25 15:00:52 by fabdul-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_pipe_error(t_lexer *list)
{
	if (list && list->token == PIPE)
		return (1);
	if (!list)
		return (1);
	return (0);
}

char	**set_command_args(char **str, t_lexer **list, int no_args)
{
	int	i;

	i = 0;
	while (i < no_args && (*list)->word)
	{
		if ((*list)->word)
		{
			str[i] = ft_strdup((*list)->word);
			delete_one_node(list, (*list)->index);
		}
		i++;
	}
	str[i] = NULL;
	return (str);
}

void	free_node(t_command *node, char **str)
{
	if (node)
		free_command(node);
	free (str);
}

t_command	*init_command(t_lexer **list, t_shell *shell)
{
	char		**str;
	int			no_args;
	t_command	*node;

	no_args = count_args(*list);
	node = (t_command *) malloc(sizeof(t_command));
	str = (char **) malloc (sizeof(char *) * (no_args + 1));
	if (!node || !str)
	{
		print_error(2);
		return (NULL);
	}
	init_node(&node);
	node->num_redirection = count_redirection(*list);
	if (node->num_redirection)
	{
		if (handle_redirection(list, &node, node->num_redirection, shell))
		{
			free_node(node, str);
			return (NULL);
		}
	}
	node->args = set_command_args(str, list, no_args);
	return (node);
}

int	parser(t_lexer **list, t_shell *shell)
{
	t_command	*node;

	node = NULL;
	shell->no_of_pipes = count_pipes(*list);
	if (!shell->no_of_pipes)
	{
		node = init_command(list, shell);
		return (add_command_node(&shell->command, node));
	}
	else
	{
		if ((*list)->token == PIPE)
			return (print_parse_error(2, shell, list));
		while (*list)
		{
			if ((*list)->token == PIPE)
				delete_one_node(list, (*list)->index);
			if (handle_pipe_error(*list))
				return (print_parse_error(2, shell, list));
			node = init_command(list, shell);
			if (add_command_node(&shell->command, node))
				return (1);
		}
	}
	return (0);
}
