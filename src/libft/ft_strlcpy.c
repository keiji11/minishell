/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llucente <llucente@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 16:15:05 by llucente          #+#    #+#             */
/*   Updated: 2021/08/23 16:15:06 by llucente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	int	i;

	if (!dst)
		return (0);
	i = -1;
	if (size)
	{
		while (++i < (int)size - 1 && src[i])
			dst[i] = src[i];
		dst[i] = '\0';
	}
	return (ft_strlen(src));
}
