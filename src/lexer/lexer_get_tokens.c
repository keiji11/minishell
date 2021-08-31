/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_get_tkns.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llucente <llucente@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 16:07:05 by llucente          #+#    #+#             */
/*   Updated: 2021/08/23 16:07:06 by llucente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/*
* begining is bach_slash "\"
* begining is single_quoting '
* begining is double_quoting "
* no quoting
*/
static int	check_the_beginning_of_word(int c)
{
	if (c == 92)
		return (1);
	else if (c == 39)
		return (2);
	else if (c == 34)
		return (3);
	else
		return (0);
}

static void	add_token_and_increament_index(t_token *tkns_list, char *word,
			int *table, int j)
{
	add_token(tkns_list, WORD, word, table[3]);
	table[1] = j;
	table[3]++;
}

void	ft_get_word(t_token *tkns_list, char *line, int *table)
{
	int		quoting;
	char	*word;
	int		j;

	j = 0;
	quoting = -1;
	word = NULL;
	j = table[1];
	while (line[j])
	{
		quoting = check_the_beginning_of_word(line[j]);
		if (quoting == 0)
		{
			word = ft_get_words(line, &j, word, &quoting);
			if (ft_strchr("\t ><|;", line[j]))
				break ;
		}
		else if (quoting > 0)
		{
			word = ft_get_words(line, &j, word, &quoting);
			if (line[j] == ' ' || line[j] == '\t')
				break ;
		}
	}
	add_token_and_increament_index(tkns_list, word, table, j);
}
