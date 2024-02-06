/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabdul-k <fabdul-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 17:35:05 by fabdul-k          #+#    #+#             */
/*   Updated: 2024/02/02 17:36:53 by fabdul-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	exec_single(t_shell *shell_data)
{
	if (shell_data->heredoc)
		create_heredoc(shell_data, shell_data->command);
	if (g_sig_interrupt == 1 || (shell_data->command->args[0] == NULL
			&& shell_data->command->redirection == NULL))
		return ;
	shell_data->command = call_expander(shell_data, shell_data->command);
	execute_single_process(shell_data->command, shell_data);
}

void	run_minishell(t_shell *shell_data, char *input)
{
	t_lexer	*lex;
	int		fd[2];

	lex = NULL;
	g_sig_interrupt = 100;
	if (init_lexer(input, &lex))
		return ;
	if (parser(&lex, shell_data))
		return ;
	shell_data->heredoc = check_heredoc(shell_data->command->redirection);
	if (shell_data->no_of_pipes == 0)
		exec_single(shell_data);
	else if (g_sig_interrupt != 1)
	{
		shell_data->child_pid = ft_calloc(shell_data->no_of_pipes + 1,
				sizeof(pid_t));
		execute_multiple_process(shell_data, fd);
	}
	g_sig_interrupt = 0;
}

int	check_args(int ac, char **av)
{
	(void)av;
	if (ac != 1)
	{
		print_error(1);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	check_signal(char *input, t_shell *data)
{
	if (handle_eof(input))
		exit_mini_shell(data, 0);
	if (g_sig_interrupt == 1)
		data->status_code = SIGNAL_ERROR;
}

int	main(int ac, char **av, char **env)
{
	t_shell	*shell_data;
	char	*input;

	if (check_args(ac, av))
		return (EXIT_FAILURE);
	shell_data = (t_shell *)malloc(sizeof(t_shell));
	if (init_shell_data(shell_data, env))
	{
		while (1)
		{
			g_sig_interrupt = 102;
			init_signals();
			input = readline(shell_data->prompt_str);
			check_signal(input, shell_data);
			if (input && input[0] && g_sig_interrupt != 1)
			{
				add_history(input);
				if (input && input[0] && check_quotes(input, shell_data))
					run_minishell(shell_data, input);
				reset_struct(shell_data);
				free(input);
			}
		}
	}
	return (EXIT_SUCCESS);
}
