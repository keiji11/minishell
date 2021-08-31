/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expnd_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llucente <llucente@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 16:03:35 by llucente          #+#    #+#             */
/*   Updated: 2021/08/31 15:32:17 by llucente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/execution.h"

t_simple_cmd	*ft_handle_cmd_expnding(t_simple_cmd **cmd)
{
	char	**splited;
	int		i;
	t_args	*new_args;
	t_args	*tmp;

	i = 1;
	splited = ft_split((*cmd)->command, ' ');
	free((*cmd)->command);
	(*cmd)->command = splited[0];
	new_args = (t_args *)malloc(sizeof(t_args));
	tmp = new_args;
	while (splited[i])
	{
		ft_assign_value_to_arg(splited, i, &new_args);
		i++;
	}
	if (i > 1)
	{
		new_args->next = (*cmd)->args;
		(*cmd)->args = tmp;
	}
	else
		free(new_args);
	free(splited);
	return (*cmd);
}

void	ft_expnd_command(t_simple_cmd **cmd, t_env **env, char **last_env)
{
	char	*befor_expnd_cmd;
	char	*after_expnd_cmd;
	char	*space;

	space = NULL;
	befor_expnd_cmd = NULL;
	after_expnd_cmd = NULL;
	befor_expnd_cmd = ft_strdup((*cmd)->command);
	ft_replace_space_by_tab(cmd, 1);
	(*cmd)->inside_quotes = check_exiting_of_quotes(((*cmd)->command));
	ft_expnd_word(&((*cmd)->command), env, last_env, 0);
	if ((*cmd)->command)
		after_expnd_cmd = ft_strdup((*cmd)->command);
	if ((*cmd)->inside_quotes == 0 && after_expnd_cmd
		&& ft_strcmp(befor_expnd_cmd, after_expnd_cmd)
		&& ft_strchr(after_expnd_cmd, ' ')
		&& ft_strchr(befor_expnd_cmd, '$'))
	{
		space = ft_strchr(after_expnd_cmd, ' ');
		if (++space)
			*cmd = ft_handle_cmd_expnding(cmd);
	}
	free(befor_expnd_cmd);
	free(after_expnd_cmd);
}

void	ft_handle_empty_command(t_simple_cmd **cmd)
{
	t_args	*args;
	t_args	*to_free;

	args = (*cmd)->args;
	if (args)
	{
		if (args->value)
		{
			(*cmd)->command = ft_strdup(args->value);
			free(args->value);
		}
		(*cmd)->inside_quotes = args->inside_quotes;
		if (args->next != NULL)
		{
			to_free = args;
			(*cmd)->args = args->next;
			free(to_free);
			to_free = NULL;
		}
		else
		{
			free((*cmd)->args);
			(*cmd)->args = NULL;
		}
	}
}
