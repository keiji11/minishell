/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llucente <llucente@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 16:10:04 by llucente          #+#    #+#             */
/*   Updated: 2021/08/23 16:10:05 by llucente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include "../headers/execution.h"

char	*return_last_argument(char	**split)
{
	char	*last_args;

	last_args = ft_strdup(split[0]);
	free(split[0]);
	free(split);
	return (last_args);
}

char	*ft_return_last_argmnt(char *argument_value)
{
	char	**split;

	split = ft_split(argument_value, '=');
	if (split[0] == NULL)
		split[0] = ft_strdup("=");
	else
	{
		if (split[0][0] != argument_value[0])
		{
			free(split[0]);
			split[0] = ft_strdup(argument_value);
		}
	}
	free(split[1]);
	if (split[0])
		return (return_last_argument(split));
	else
	{
		free(split);
		return (NULL);
	}
}

char	*ft_get_last_arg__in_export(t_args	**args,
		t_pipe_line **current_pipe_line)
{
	while ((*args)->next != NULL)
		(*args) = (*args)->next;
	if ((*current_pipe_line)->child->command
		&&!ft_strcmp((*current_pipe_line)->child->command, "export"))
		return (ft_return_last_argmnt((*args)->value));
	else
	{
		if ((*args)->value)
			return (ft_strdup((*args)->value));
		else
		{
			if ((*current_pipe_line)->child->command)
				return (ft_strdup((*current_pipe_line)->child->command));
		}
	}
	return (NULL);
}

char	*get_last_argument_or_command(t_pipe_line *current_pipe_line)
{
	t_args	*args;

	if (current_pipe_line->child->next != NULL)
		return (NULL);
	else
	{
		args = current_pipe_line->child->args;
		if (args == NULL)
		{
			if (current_pipe_line->child->command)
				return (ft_strdup(current_pipe_line->child->command));
		}
		else
		{
			return (ft_get_last_arg__in_export(&args, &current_pipe_line));
		}
	}
	return (NULL);
}
