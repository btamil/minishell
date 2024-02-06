/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponnusa <tponnusa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 18:38:36 by tponnusa          #+#    #+#             */
/*   Updated: 2024/02/02 12:30:54 by tponnusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_array_of_string(char **s)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}

void	free_list(t_env_list *lst)
{
	t_env_list	*tmp;

	tmp = lst;
	while (tmp)
	{
		tmp = lst->next;
		free(lst->key);
		free(lst->value);
		free(lst);
		lst = tmp;
	}
	free(lst);
}

void	free_lexer_list(t_lexer *lex)
{
	t_lexer	*temp;

	temp = lex;
	while (lex != NULL)
	{
		temp = lex->next;
		if (lex->word)
			free(lex->word);
		free(lex);
		lex = temp;
	}
}

void	free_command(t_command *com)
{
	t_command	*temp;
	int			i;

	temp = com;
	while (com != NULL)
	{
		if (com->args)
		{
			i = 0;
			while (com->args[i] != NULL)
			{
				free(com->args[i]);
				i++;
			}
			free(com->args);
			com->args = NULL;
		}
		if (com->hd_file_name != NULL)
			free(com->hd_file_name);
		if (com->redirection)
			free_lexer_list(com->redirection);
		temp = com->next;
		free(com);
		com = temp;
	}
}

void	close_all_pipe_fds(int fd_in, int pipe_in, int pipe_out)
{
	if (pipe_in > 2)
		close(pipe_in);
	if (pipe_out > 2)
		close(pipe_out);
	if (fd_in > 2)
		close(fd_in);
}
