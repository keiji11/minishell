/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llucente <llucente@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 16:13:01 by llucente          #+#    #+#             */
/*   Updated: 2021/08/23 16:13:02 by llucente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*dstt;
	unsigned char	*srcc;

	srcc = (unsigned char *)src;
	dstt = (unsigned char *)dst;
	i = 0;
	while (i < n)
	{
		dstt[i] = srcc[i];
		if (srcc[i] == (unsigned char)c)
			return (dstt + ++i);
		i++;
	}
	return (0);
}
