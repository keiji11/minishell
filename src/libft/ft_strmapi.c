/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llucente <llucente@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 16:15:19 by llucente          #+#    #+#             */
/*   Updated: 2021/08/23 16:15:20 by llucente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*rst;
	size_t	i;

	if (!s)
		return (NULL);
	rst = (char *)malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!rst)
		return (NULL);
	i = 0;
	while (s[i])
	{
		rst[i] = f(i, s[i]);
		i++;
	}
	rst[i] = '\0';
	return (rst);
}
