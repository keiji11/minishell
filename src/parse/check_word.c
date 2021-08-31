/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llucente <llucente@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 16:08:01 by llucente          #+#    #+#             */
/*   Updated: 2021/08/31 15:28:47 by llucente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	count_backslashes(char *word, int *index, int back_slash)
{
	while (word[*index] == 92)
	{
		back_slash++;
		(*index)++;
	}
	return (back_slash);
}

int	ft_get_first_double_quotes(char *word, int *index, int *back_slash)
{
	int	quote;

	quote = 0;
	if (*index != 0 && word[*index - 1] != 92)
		quote += 2;
	else
	{
		if (*back_slash % 2 == 0)
			quote += 2;
	}
	(*index)++;
	*back_slash = 0;
	return (quote);
}

int	ft_get_first_single_quotes(char *word, int *index, int *back_slash)
{
	int	quote;

	quote = 0;
	if (word[*index - 1] != 92)
	{
		quote += 1;
	}
	else
	{
		if (*back_slash % 2 == 0)
		{
			quote += 1;
		}
	}
	(*index)++;
	*back_slash = 0;
	return (quote);
}

void	ft_get_close_double_quotes(char *word, int *index, int *back_slash,
																	int *quote)
{
	if (word[*index - 1] != 92)
		*quote -= 2;
	else
	{
		if (*back_slash % 2 == 0)
			*quote -= 2;
	}
	*back_slash = 0;
	(*index)++;
}

void	ft_get_close_single_quotes(int *index, int *back_slash,
																	int *quote)
{
	(*index)++;
	*quote -= 1;
	*back_slash = 0;
}
