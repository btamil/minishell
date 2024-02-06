/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabdul-k <fabdul-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 18:28:49 by fabdul-k          #+#    #+#             */
/*   Updated: 2024/01/25 17:03:23 by fabdul-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "minishell.h"

size_t	dollar_index(char *str);

char	*char_to_str(char c);
char	*delete_quote(char *str);
char	*handle_remaining_char(char *str, int j, char **tmp);
int		check_if_not_alphnum(char *str);
int		check_enclosed(char*str, int j, int *pos);
char	find_first_quote(char *str, int *pos);
int		find_closing(char *str, int start, char q);

#endif