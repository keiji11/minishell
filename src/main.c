/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llucente <llucente@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 16:10:13 by llucente          #+#    #+#             */
/*   Updated: 2021/08/31 12:45:00 by llucente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include "../headers/execution.h"

void	show_prompt(void)
{
	write(1, GREEN, ft_strlen(GREEN));
	write(1, "minishell$ ", strlen("minishell$ "));
	write(1, RESET, ft_strlen(RESET));
}

t_simple_cmd	*ft_del_empty_node_btwn(t_simple_cmd	**head,
		t_simple_cmd **temp)
{
	t_simple_cmd	*prev;

	prev = NULL;
	while (*temp != NULL)
	{
		while ((*temp) != NULL && ((*temp)->inside_quotes != 0
				|| ((*temp)->command && (*temp)->inside_quotes == 0)))
		{
			prev = (*temp);
			(*temp) = (*temp)->next;
		}
		if ((*temp) == NULL)
			return (*head);
		if (prev)
		{
			prev->next = (*temp)->next;
			ft_destroy_simple((*temp));
			(*temp) = prev->next;
		}
		else
			(*temp) = (*temp)->next;
	}
	return (*head);
}

t_simple_cmd	*ft_del_empty_simple_cmds(t_pipe_line **pipe_line)
{
	t_simple_cmd	*head;
	t_simple_cmd	*temp;

	head = (*pipe_line)->child;
	temp = head;
	while (temp != NULL && (!temp->command && temp->inside_quotes == 0)
		&& temp->args == NULL && temp->redirections == NULL)
	{
		head = temp->next;
		ft_destroy_simple(temp);
		temp = head;
	}
	*head = *ft_del_empty_node_btwn(&head, &temp);
	return (head);
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	ft_minishell(env);
	return (0);
}
