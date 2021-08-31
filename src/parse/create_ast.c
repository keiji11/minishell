/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llucente <llucente@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 16:08:08 by llucente          #+#    #+#             */
/*   Updated: 2021/08/31 15:17:55 by llucente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

t_pipe_line	*ft_init_pipe_line(void)
{
	t_pipe_line		*pipe_line;

	pipe_line = (t_pipe_line *)malloc(sizeof(t_pipe_line));
	if (!pipe_line)
		return (NULL);
	pipe_line->next = NULL;
	pipe_line->child = NULL;
	pipe_line->simple_cmd_count = 0;
	return (pipe_line);
}

t_pipe_line	*reset_pipe_line_head(t_pipe_line **pipe_line, t_simple_cmd *head)
{
	(*pipe_line)->child = head;
	return (*pipe_line);
}

t_pipe_line	*ft_create_pieline(t_token **tkns)
{
	t_pipe_line		*pipe_line;
	t_simple_cmd	*head;
	t_simple_cmd	*current_cmd;

	pipe_line = ft_init_pipe_line();
	current_cmd = NULL;
	head = NULL;
	while ((*tkns)->type != NEWLINE)
	{
		if (head == NULL)
		{
			head = ft_create_simple_cmd(tkns);
			pipe_line->simple_cmd_count += 1;
		}
		else
		{
			if ((*tkns)->type == SEMI || (*tkns)->type == NEWLINE)
				break ;
			(*tkns) = (*tkns)->next;
			current_cmd = ft_create_simple_cmd(tkns);
			ft_insert_simple_cmd(head, current_cmd);
			pipe_line->simple_cmd_count += 1;
		}
	}
	return (reset_pipe_line_head(&pipe_line, head));
}

void	ft_create_next_pipeline(t_token *tkns_list, t_command_list **head)
{
	t_pipe_line		*current_pipeline;

	current_pipeline = NULL;
	current_pipeline = (*head)->childs;
	while (current_pipeline->next != NULL)
		current_pipeline = current_pipeline->next;
	if (tkns_list->type != NEWLINE && tkns_list->type != SEMI)
	{
		current_pipeline->next = ft_create_pieline(&tkns_list);
		(*head)->pipe_line_count += 1;
	}
}

t_command_list	*ft_create_ast(t_token *tkns_list)
{
	t_command_list	*head;

	head = init_cmd_list();
	while (tkns_list->type != NEWLINE)
	{
		if (head->childs == NULL)
		{
			head->childs = ft_create_pieline(&tkns_list);
			head->pipe_line_count += 1;
		}
		else if (tkns_list->type == SEMI)
		{
			tkns_list = tkns_list->next;
			ft_create_next_pipeline(tkns_list, &head);
		}
		else
			tkns_list = tkns_list->next;
	}
	return (head);
}
