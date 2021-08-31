/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llucente <llucente@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 16:07:13 by llucente          #+#    #+#             */
/*   Updated: 2021/08/31 15:17:55 by llucente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_destoy_token_list(t_token *tkns_list)
{
	t_token	*tmp;

	tmp = NULL;
	while (tkns_list->type != NEWLINE)
	{
		tmp = tkns_list;
		tkns_list = tkns_list->next;
		free(tmp->value);
		tmp->value = NULL;
		free(tmp);
		tmp = NULL;
	}
	if (tkns_list->type == NEWLINE)
	{
		free(tkns_list->value);
		tkns_list->value = NULL;
		free(tkns_list);
		tkns_list = NULL;
		write(1, CYAN, ft_strlen(CYAN));
	}
}

t_token	*first_token(void)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	new_token->value = ft_strdup("NONE");
	new_token->next = NULL;
	new_token->type = NONE;
	new_token->index = 0;
	return (new_token);
}

void	add_token(t_token *token_list, t_token_type type,
			   char *content, int index)
{
	t_token	*tmp;

	tmp = token_list;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = (t_token *)malloc(sizeof(t_token));
	tmp->next->index = index;
	tmp->next->type = type;
	tmp->next->value = content;
	tmp->next->next = NULL;
}

/*
 * table[5];
 * 0 = i  ; 1 = j ; k = 2; index = 3 ; quote = 4;
 * */
void	create_tkns_list(t_token *tkns_list, char *line)
{
	int	table[5];

	table[3] = 1;
	table[4] = 0;
	table[0] = 0;
	while (line[table[0]])
	{
		table[1] = table[0];
		while (line[table[1]] == ' ' || line[table[1]] == '\t')
			table[1]++;
		if (ft_strrchr("|;><", line[table[1]]) != NULL)
			get_space_pipe_semi_redir(tkns_list, line, &table[1], &table[3]);
		if (ft_strrchr("\t <>;|", line[table[1]]) == NULL
			|| line[table[1]] == '\\')
		{
			table[2] = table[1];
			ft_get_word(tkns_list, line, table);
		}
		table[0] = table[1];
	}
	add_token(tkns_list, NEWLINE, ft_strdup("newline"), table[3]);
}

t_token	*ft_lexer(char *line)
{
	t_token	*tkns_list;

	tkns_list = NULL;
	tkns_list = first_token();
	create_tkns_list(tkns_list, line);
	return (tkns_list);
}
