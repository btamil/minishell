/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabdul-k <fabdul-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 09:17:43 by fabdul-k          #+#    #+#             */
/*   Updated: 2023/11/21 09:17:43 by fabdul-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*expander_str(t_shell *shell, char *str, int here_doc)
{
	char	*temp;

	(void)shell;
	temp = NULL;
	if (dollar_index(str) != 0)
	{
		if (str[dollar_index(str)] != ' '
			&& str[dollar_index(str)] != '\0')
		{
			temp = handle_dollar(shell, str);
			free (str);
			str = temp;
		}
	}
	if (!here_doc)
		if (ft_strchr(str, 34) || ft_strchr(str, 39))
			str = delete_quote(str);
	return (str);
}

char	**expander(t_shell *shell, char **str)
{
	int		i;
	char	*temp;

	i = 0;
	temp = NULL;
	while (str[i])
	{
		if (dollar_index(str[i]) != 0)
		{
			if (str[i][dollar_index(str[i])] != ' '
				&& str[i][dollar_index(str[i])] != '\0')
			{
				temp = handle_dollar(shell, str[i]);
				free (str[i]);
				str[i] = temp;
			}
		}
		if (ft_strchr(str[i], 34) || ft_strchr(str[i], 39))
			str[i] = delete_quote(str[i]);
		i++;
	}
	return (str);
}

t_command	*call_expander(t_shell *shell, t_command *cmd)
{
	t_lexer	*beg;

	cmd->args = expander(shell, cmd->args);
	beg = cmd->redirection;
	while (cmd->redirection)
	{
		if (cmd->redirection->token != LESS_LESS)
			cmd->redirection->word
				= expander_str(shell, cmd->redirection->word, 0);
		cmd->redirection = cmd->redirection->next;
	}
	cmd->redirection = beg;
	return (cmd);
}
