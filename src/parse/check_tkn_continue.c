/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token_continue.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llucente <llucente@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 16:07:50 by llucente          #+#    #+#             */
/*   Updated: 2021/08/31 15:17:55 by llucente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_print_systax_error(t_token *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 1);
	ft_putstr_fd(token->value, 1);
	ft_putstr_fd("'\n", 1);
}

int	check_redirection(t_token *tkns_list, t_token *token, int *status)
{
	int	result;

	result = 0;
	if (token->type != WORD)
	{
		ft_print_systax_error(token);
		ft_destoy_token_list(tkns_list);
		*status = 258;
		result = 1;
	}
	return (result);
}
