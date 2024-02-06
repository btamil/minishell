/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponnusa <tponnusa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:29:15 by tponnusa          #+#    #+#             */
/*   Updated: 2024/02/02 13:09:25 by tponnusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	print_parse_error(int i, t_shell *shell, t_lexer **list)
{
	if (i == 1)
		ft_putstr_fd("Error- Quotes are not closed properly\n", 2);
	else if (i == 2)
	{
		ft_putstr_fd("Error- Syntax error near unexpected token\n", 2);
		shell->status_code = 258;
	}
	else if (i == 3)
	{
		ft_putstr_fd("Error- Syntax error near unexpected token 'newline'\n",
			2);
		shell->status_code = 258;
	}
	if (*list)
		free_lexer_list(*list);
	return (1);
}

void	print_error(int i)
{
	if (i == 1)
		ft_putstr_fd("MiniShell - doesnot require arguments\n", 2);
	else if (i == 2)
		ft_putstr_fd("Error: System is unable to allocate memory\n", 2);
	else if (i == 3)
		ft_putstr_fd("Error: In getting CWD\n", 2);
	else if (i == 4)
		ft_putstr_fd("Error: In creating child process by fork()\n", 2);
	else if (i == 5)
		ft_putstr_fd("env: No such file or directory\n", 2);
	else if (i == 6)
		ft_putstr_fd("Error: HOME not set\n", 2);
	else if (i == 7)
		ft_putstr_fd("Error: In changing Directory\n", 2);
	else if (i == 8)
		ft_putstr_fd("minishell: cd: Not a directory\n", 2);
	else if (i == 9)
		ft_putstr_fd("minishell: cd: No such file or direcory\n", 2);
	else if (i == 10)
		ft_putstr_fd("minishell: cd:  too many arguments\n", 2);
}

void	print_error_exec(int i)
{
	if (i == 10)
		ft_putstr_fd("Error: No PATH found!!!\n", 2);
	else if (i == 11)
		ft_putstr_fd("Error: In System Execution!!!\n", 2);
	else if (i == 12)
		ft_putstr_fd("minishell: export: not a valid identifier\n", 2);
	else if (i == 13)
		ft_putstr_fd("minishell: unset: not a valid identifier\n", 2);
	else if (i == 16)
		ft_putstr_fd("minishell: Error: In calling pipe()\n", 2);
	else if (i == 17)
		ft_putstr_fd("Command not found\n", 2);
	else if (i == 18)
		ft_putstr_fd("minishell: redir : No such file or directory\n", 2);
	else if (i == 19)
		ft_putstr_fd("minishell: Error: In calling dup()\n", 2);
	else if (i == 20)
		ft_putstr_fd("minishell: Error: In creating file for Heredoc\n", 2);
	else if (i == 21)
		ft_putstr_fd("minishell: Error: In creating file \n", 2);
}

void	print_error2(int i, t_shell *data)
{
	if (i == 14)
	{
		ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
		data -> status_code = 255;
		exit_mini_shell(data, 0);
	}
	else if (i == 15)
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
}
