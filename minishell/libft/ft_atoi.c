/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponnusa <tponnusa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:57:03 by tponnusa          #+#    #+#             */
/*   Updated: 2023/11/07 18:21:08 by tponnusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(int c)
{
	if ((c >= 9 && c <= 13) || (c == 32))
		return (1);
	return (0);
}

long long	ft_atoi(const char *str)
{
	long long	i;
	int			sign;
	long long	value;

	i = 0;
	sign = 1;
	value = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		value = (value * 10) + (str[i] - '0');
		i++;
	}
	return (value * sign);
}
