/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabdul-k <fabdul-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 18:28:07 by fabdul-k          #+#    #+#             */
/*   Updated: 2024/02/01 19:08:56 by fabdul-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*create_hd_file(int i)
{
	char	*num;
	char	*file_name;

	num = ft_itoa(i);
	file_name = ft_strjoin("heredoc_file_", num);
	free(num);
	return (file_name);
}

char	*get_file_name(char *file, t_shell *data, t_command *cmd, int i)
{
	if (file != NULL)
		free(data->command->hd_file_name);
	cmd->hd_file_name = create_hd_file(i);
	return (cmd->hd_file_name);
}
