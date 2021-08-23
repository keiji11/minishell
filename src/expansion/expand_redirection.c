/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llucente <llucente@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 16:05:36 by llucente          #+#    #+#             */
/*   Updated: 2021/08/23 16:05:37 by llucente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/execution.h"

void	check_word_expand_redtion(int redirection, char **expanded,
		char **word, char **string)
{
	if (redirection == 1)
	{
		if (*expanded != NULL && (*expanded)[0] != '\0')
		{
			*string = *expanded;
		}
		else
		{
			*string = ft_strdup(*word);
		}
	}
	else
	{
		*string = *expanded;
	}
	free(*word);
}

void	ft_expande_redirection(t_simple_cmd **cmd, t_env **env, char **last_env)
{
	t_redirection	*redis;

	redis = NULL;
	redis = (*cmd)->redirections;
	while (redis)
	{
		redis->inside_quotes = check_exiting_of_qoutes(redis->file_name);
		if (redis->inside_quotes != 0)
			ft_expande_word(&redis->file_name, env, last_env, 0);
		else
			ft_expande_word(&redis->file_name, env, last_env, 1);
		redis = redis->next;
	}
}
