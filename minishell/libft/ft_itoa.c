/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponnusa <tponnusa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 19:43:05 by tponnusa          #+#    #+#             */
/*   Updated: 2022/11/28 16:49:17 by tponnusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_find_total_digits(int n)
{
	int	c;

	c = 0;
	if (n < 0)
	{
		n = -n;
		c = 1;
	}
	while (n)
	{
		c++;
		n = n / 10;
	}
	return (c);
}

static char	*ft_convert_string(int num, char *str, int len)
{
	if (num == 0)
		str[0] = '0';
	else if (num < 0)
	{
		str[0] = '-';
		if (num == -2147483648)
		{
			len = len - 1;
			str[len] = '8';
			num = num / 10;
		}
		num = -num;
	}
	while (num != 0 && len--)
	{
		str[len] = (num % 10) + '0';
		num = num / 10;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	int		dlen;
	char	*str;

	dlen = 0;
	if (n == 0)
		dlen = 1;
	else
		dlen = ft_find_total_digits(n);
	str = malloc(dlen + 1);
	if (!str)
		return (0);
	str[dlen] = '\0';
	str = ft_convert_string(n, str, dlen);
	return (str);
}
