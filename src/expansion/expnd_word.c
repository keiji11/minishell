/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expnd_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llucente <llucente@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 16:06:05 by llucente          #+#    #+#             */
/*   Updated: 2021/08/31 15:32:17 by llucente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/execution.h"

int	check_exiting_of_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			return (1);
		}
		else if (str[i] == '\"')
			return (2);
		i++;
	}
	return (0);
}

void	ft_expnd_squence_of_dollar_sign(char *str, int *i, char **expndd)
{
	char	*tmp1;
	char	*tmp;

	tmp1 = *expndd;
	tmp = ft_substr(str, *i, 2);
	*expndd = ft_strjoin(*expndd, tmp);
	free(tmp1);
	free(tmp);
	*i += 2;
}

void	ft_replace_env_by_value(char *str, int *i, char **expndd,
		char **env_value)
{
	char	*tmp;

	tmp = *expndd;
	*expndd = ft_strjoin(*expndd, *env_value);
	free(*env_value);
	free(tmp);
	if (str[*i] == '$')
		(*i)++;
	if (str[*i] == '_')
		(*i)++;
	else
	{
		while (ft_isalpha(str[*i]) || ft_isalnum(str[*i])
			|| str[*i] == '_')
			(*i)++;
	}	
}

void	ft_skip_characters_env_not_exist(char *str, int *i)
{
	if (str[*i] == '$')
		(*i)++;
	while (ft_isalpha(str[*i]) || ft_isalnum(str[*i])
		|| str[*i] == '_')
		(*i)++;
}

void	ft_expnd_word(char **string, t_env **env_list, char **last_env,
		int redirection)
{
	t_expansion	expd;
	int			i;

	i = 0;
	expd.word = *string;
	expd.expndd = NULL;
	ft_replace_tilde(&expd.word);
	while (expd.word[i])
	{
		if (expd.word[i] == '\\')
			ft_expnd_backslashes(expd.word, &i, &expd.expndd);
		else if (expd.word[i] == '\'')
			ft_rmv_single_quotes(expd.word, &i, &expd.expndd);
		else if (expd.word[i] == '"')
			expd.expndd = ft_expnd_double_quotes(expd, &i, env_list,
					last_env);
		else if (expd.word[i] == '$')
			ft_expnd_env_variable(&expd, &i, env_list, last_env);
		else
			ft_get_char(expd.word, &i, &expd.expndd);
	}
	check_word_expnd_redtion(redirection, &expd.expndd, &expd.word, string);
}
