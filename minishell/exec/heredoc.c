/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabdul-k <fabdul-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:26:19 by tponnusa          #+#    #+#             */
/*   Updated: 2024/02/02 17:30:14 by fabdul-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_heredoc(t_lexer *redirs)
{
	t_lexer	*temp;

	temp = redirs;
	while (temp)
	{
		if (temp->token && temp->token == LESS_LESS)
			return (1);
		temp = temp->next;
	}
	return (0);
}

void	run_hd_process(char *delimiter, t_shell *data, int fd, int flag)
{
	char	*hd_input;

	hd_input = readline("> ");
	while (g_sig_interrupt != 1 && hd_input
		&& (ft_strcmp(delimiter, hd_input) != 0))
	{
		if (flag)
			hd_input = expander_str(data, hd_input, 1);
		write(fd, hd_input, ft_strlen(hd_input));
		write(fd, "\n", 1);
		free(hd_input);
		if (g_sig_interrupt == 1)
			break ;
		hd_input = readline("> ");
		if (!hd_input)
			break ;
	}
	free(hd_input);
	close(fd);
	if (handle_eof(hd_input))
		exit_mini_shell(data, 0);
	if (!hd_input)
		exit_mini_shell(data, 0);
}

void	start_heredoc(t_shell *data, char *delimiter, char *file_name, int flag)
{
	int		fd;

	if (g_sig_interrupt != 1)
	{
		fd = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
		run_hd_process(delimiter, data, fd, flag);
		data->status_code = EXIT_SUCCESS;
	}
	if (g_sig_interrupt == 1)
		data->status_code = SIGNAL_ERROR;
}

void	create_heredoc(t_shell *data, t_command *cmd)
{
	t_lexer		*redirs;
	static int	i;
	int			flag;

	flag = 1;
	redirs = NULL;
	if (cmd)
		redirs = cmd->redirection;
	while (redirs)
	{
		if (redirs->token == LESS_LESS)
		{
			cmd->hd_file_name = get_file_name(cmd->hd_file_name, data, cmd, i);
			if (ft_strchr(redirs->word, '\"'))
			{
				flag = 0;
				redirs->word = delete_quote(redirs->word);
			}
			g_sig_interrupt = 101;
			start_heredoc(data, redirs->word, cmd->hd_file_name, flag);
		}
		redirs = redirs->next;
		i++;
	}
}
