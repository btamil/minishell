/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponnusa <tponnusa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:52:00 by tponnusa          #+#    #+#             */
/*   Updated: 2024/02/01 14:39:03 by tponnusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	change_redir_to_write(int i, t_lexer *redirection)
{
	int	write_fd;

	write_fd = 0;
	if (i == 1)
		write_fd = open(redirection->word, O_CREAT | O_RDWR | O_TRUNC, 0644);
	else
		write_fd = open(redirection->word, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (write_fd < 0)
	{
		print_error_exec(21);
		return (EXIT_FAILURE);
	}
	if (write_fd > 0 && dup2(write_fd, STDOUT_FILENO) < 0)
	{
		print_error_exec(19);
		return (EXIT_FAILURE);
	}
	if (write_fd > 0)
		close(write_fd);
	return (EXIT_SUCCESS);
}

int	change_redir_to_read(char *file_name)
{
	int	read_fd;

	read_fd = open(file_name, O_RDONLY);
	if (read_fd < 0)
	{
		print_error_exec(18);
		return (EXIT_FAILURE);
	}
	if (read_fd && dup2(read_fd, STDIN_FILENO) < 0)
	{
		print_error_exec(19);
		return (EXIT_FAILURE);
	}
	if (read_fd > 0)
		close(read_fd);
	return (EXIT_SUCCESS);
}

int	check_redir_to_write(t_lexer *redir)
{
	if (redir->token == GREAT)
	{
		if (change_redir_to_write(1, redir))
			return (EXIT_FAILURE);
	}
	else if (redir->token == GREAT_GREAT)
	{
		if (change_redir_to_write(2, redir))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	check_redirections(t_command *cmd)
{
	t_lexer	*tmp;

	tmp = cmd->redirection;
	while (tmp)
	{
		if (tmp->token == LESS)
		{
			if (change_redir_to_read(tmp->word))
				return (EXIT_FAILURE);
		}
		else if (tmp->token == LESS_LESS)
		{
			if (change_redir_to_read(cmd->hd_file_name))
				return (EXIT_FAILURE);
		}
		else if (check_redir_to_write(tmp))
			return (EXIT_FAILURE);
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}
