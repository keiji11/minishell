/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llucente <llucente@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 16:08:54 by llucente          #+#    #+#             */
/*   Updated: 2021/08/31 15:17:55 by llucente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

t_redirection	*ft_create_redirection(t_token **tkns, int index)
{
	t_redirection	*redirection;

	redirection = (t_redirection *)malloc(sizeof(t_redirection));
	if (!redirection)
		return (NULL);
	redirection->index = index;
	redirection->next = NULL;
	if ((*tkns)->type == GREAT)
		redirection->type = RE_GREAT;
	else if ((*tkns)->type == DOUBLE_GREAT)
		redirection->type = RE_DOUBLE_GREAT;
	else if ((*tkns)->type == LESS)
		redirection->type = RE_LESS;
	(*tkns) = (*tkns)->next;
	redirection->file_name = ft_strdup((*tkns)->value);
	(*tkns) = (*tkns)->next;
	return (redirection);
}

t_redirection	*ft_insert_redirection(t_redirection *redirection,
				t_token **tkns, int index)
{
	t_redirection	*tmp;

	tmp = NULL;
	if (redirection == NULL)
		redirection = ft_create_redirection(tkns, index);
	else
	{
		tmp = redirection;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = ft_create_redirection(tkns, index);
	}
	return (redirection);
}

void	ft_insert_arg(t_args *head, t_args *current_args)
{
	t_args	*tmp;

	tmp = head;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = current_args;
}

t_args	*ft_create_arg(char *value)
{
	t_args	*arg;

	arg = (t_args *)malloc(sizeof(t_args));
	arg->value = ft_strdup(value);
	arg->next = NULL;
	arg->inside_quotes = 0;
	return (arg);
}

t_command_list	*ft_parser(t_token *tkns_list, int *status)
{
	t_command_list	*command_list;

	command_list = NULL;
	write(1, RED, ft_strlen(RED));
	if (!ft_check_syntax(tkns_list, status))
	{
		command_list = ft_create_ast(tkns_list);
		ft_destoy_token_list(tkns_list);
	}
	return (command_list);
}
