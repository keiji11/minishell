/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llucente <llucente@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 16:06:12 by llucente          #+#    #+#             */
/*   Updated: 2021/08/31 15:32:30 by llucente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/execution.h"

void	ft_expnd_simple_cmd(t_simple_cmd **cmd, t_env **env, char **last_env)
{
	t_args			*args;

	args = NULL;
	ft_expnd_arguments(cmd, env, last_env);
	if ((*cmd)->command)
		ft_expnd_command(cmd, env, last_env);
	ft_expnd_redtion(cmd, env, last_env);
	args = (*cmd)->args;
	if (args)
		ft_delete_emty_args_nodes(&(*cmd)->args);
	if (!(*cmd)->command && (*cmd)->inside_quotes == 0)
		ft_handle_empty_command(cmd);
	ft_return_spaces(cmd);
}

void	ft_expnding(t_pipe_line *pipe_line, t_env **env, char **last_env)
{
	t_simple_cmd	*current_cmd;
	t_simple_cmd	*head_cmd;

	current_cmd = NULL;
	head_cmd = NULL;
	ft_putstr_fd(RED, 1);
	head_cmd = pipe_line->child;
	while (head_cmd)
	{
		current_cmd = head_cmd;
		ft_expnd_simple_cmd(&current_cmd, env, last_env);
		head_cmd = head_cmd->next;
	}
}
