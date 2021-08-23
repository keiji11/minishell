/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llucente <llucente@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 16:02:05 by llucente          #+#    #+#             */
/*   Updated: 2021/08/23 16:02:06 by llucente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/execution.h"

int	ft_unset(t_args *args, t_env **head)
{
	int		ret;

	ret = 0;
	while (args != NULL)
	{
		if (args->value == NULL)
			ret = ft_put_err("`'", ": not a valid identifier", 1);
		else
			ft_delete_from_list(head, args->value);
		args = args->next;
	}
	return (ret);
}
