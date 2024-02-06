/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponnusa <tponnusa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 16:55:49 by tponnusa          #+#    #+#             */
/*   Updated: 2022/11/28 11:48:26 by tponnusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;
	size_t	len;

	if (count == SIZE_MAX || size == SIZE_MAX)
		return (NULL);
	len = count * size;
	p = malloc(len);
	if (!p)
		return (0);
	ft_bzero(p, len);
	return (p);
}
