/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_get_tokens_op.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llucente <llucente@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 16:06:52 by llucente          #+#    #+#             */
/*   Updated: 2021/08/23 16:06:53 by llucente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	get_redir(t_token *tokens_list, char *line, int *j, int *index)
{
	if (line[*j] == '>')
	{
		if (line[*j + 1] == '>')
		{
			add_token(tokens_list, DOUBLE_GREAT, ft_strdup(">>"), *index);
			*j = *j + 2;
			(*index)++;
		}
		else
		{
			add_token(tokens_list, GREAT, ft_strdup(">"), *index);
			(*j)++;
			(*index)++;
		}
	}
	else if (line[*j] == '<')
	{
		add_token(tokens_list, LESS, ft_strdup("<"), *index);
		(*j)++;
		(*index)++;
	}
}

void	get_space_pipe_semi_redir(t_token *tokens_list,
							   char *line, int *j, int *index)
{
	char	*token;

	if (line[*j] == '|')
	{
		if (line[*j + 1] == '|')
			token = ft_strdup("||");
		else
			token = ft_strdup("|");
		add_token(tokens_list, PIPE, token, *index);
		(*index)++;
		(*j)++;
	}
	else if (line[*j] == ';')
	{
		if (line[*j + 1] == ';')
			token = ft_strdup(";;");
		else
			token = ft_strdup(";");
		add_token(tokens_list, SEMI, token, *index);
		(*index)++;
		(*j)++;
	}
	else
		get_redir(tokens_list, line, j, index);
}
