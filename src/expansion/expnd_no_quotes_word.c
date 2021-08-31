/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expnd_no_quotes_word.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llucente <llucente@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 19:39:44 by zjamali           #+#    #+#             */
/*   Updated: 2021/08/31 15:32:17 by llucente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/execution.h"

void	ft_rmv_single_quotes(char *str, int *i, char **expndd)
{
	int		j;
	char	*tmp1;
	char	*tmp;

	(*i)++;
	j = *i;
	while (str[j] != '\'')
		j++;
	tmp1 = *expndd;
	tmp = ft_substr(str, *i, j - *i);
	*expndd = ft_strjoin(*expndd, tmp);
	free(tmp);
	free(tmp1);
	*i = j + 1;
}

void	ft_get_char(char *str, int *i, char **expndd)
{
	char	*tmp1;
	char	*tmp;

	tmp1 = *expndd;
	tmp = ft_substr(str, *i, 1);
	*expndd = ft_strjoin(*expndd, tmp);
	free(tmp1);
	free(tmp);
	(*i)++;
}

void	ft_expnd_backslashes(char *str, int *i, char **expndd)
{
	int		j;
	char	*tmp1;
	char	*tmp;

	tmp = NULL;
	tmp1 = NULL;
	j = *i;
	while (str[j] == '\\')
	{
		tmp1 = *expndd;
		tmp = ft_substr(str, j + 1, 1);
		*expndd = ft_strjoin(*expndd, tmp);
		free(tmp1);
		free(tmp);
		j += 2;
	}
	*i = j;
}

void	ft_expnd_underscore_if_exist(char *str, int i, char **env_value,
		char *last_argmnt)
{
	if (str[i + 1] == '_' && str[i + 2] == '\0' && last_argmnt)
	{
		free(*env_value);
		*env_value = NULL;
		*env_value = ft_strdup(last_argmnt);
	}
}

void	ft_expnd_env_variable(t_expansion *expd, int *i, t_env **env_list,
		char **last_env)
{
	if (expd->word[*i + 1] == '$')
		ft_expnd_squence_of_dollar_sign(expd->word, i, &(expd->expndd));
	else
	{
		expd->tmp = get_env_variable_value(expd->word + *i, env_list);
		if (expd->tmp)
		{
			ft_expnd_underscore_if_exist(expd->word, *i, &(expd->tmp),
				last_env[1]);
			ft_replace_env_by_value(expd->word, i, &expd->expndd,
				&(expd->tmp));
		}
		else if (i == 0 || expd->word[*i - 1] != '$')
			ft_expnd_special_params(expd->word, i, &expd->expndd,
				last_env[0]);
		else
			ft_skip_char_non_env_var(expd->word, i,
				&(expd->expndd), 0);
	}
}
