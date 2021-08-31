/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expnd_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llucente <llucente@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 16:05:36 by llucente          #+#    #+#             */
/*   Updated: 2021/08/31 15:32:17 by llucente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/execution.h"

void	check_word_expnd_redtion(int redirection, char **expndd,
		char **word, char **string)
{
	if (redirection == 1)
	{
		if (*expndd != NULL && (*expndd)[0] != '\0')
		{
			*string = *expndd;
		}
		else
		{
			*string = ft_strdup(*word);
		}
	}
	else
	{
		*string = *expndd;
	}
	free(*word);
}

void	ft_expnd_redtion(t_simple_cmd **cmd, t_env **env, char **last_env)
{
	t_redirection	*redis;

	redis = NULL;
	redis = (*cmd)->redirections;
	while (redis)
	{
		redis->inside_quotes = check_exiting_of_quotes(redis->file_name);
		if (redis->inside_quotes != 0)
			ft_expnd_word(&redis->file_name, env, last_env, 0);
		else
			ft_expnd_word(&redis->file_name, env, last_env, 1);
		redis = redis->next;
	}
}
