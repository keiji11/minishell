/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expnd_double_quotes_word.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llucente <llucente@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 16:04:21 by llucente          #+#    #+#             */
/*   Updated: 2021/08/31 15:32:17 by llucente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/execution.h"

void	ft_expnd_underscore_in_double_qts(char *str, int i, char **env_value,
		char *last_argmnt)
{
	if (str[i + 1] == '_' && str[i + 2] == '"' && last_argmnt)
	{
		free(*env_value);
		*env_value = NULL;
		*env_value = ft_strdup(last_argmnt);
	}
}

void	ft_expnd_env_variable_in_dble_qte(t_expansion *expd, int *j,
		t_env **env_list, char **last_env)
{
	if (expd->word[*j + 1] == '$')
		ft_expnd_squence_of_dollar_sign(expd->word, j, &(expd->expndd));
	else
	{
		expd->tmp = get_env_variable_value(expd->word + *j, env_list);
		if (expd->tmp)
		{
			ft_expnd_underscore_in_double_qts(expd->word, *j, &(expd->tmp),
				last_env[1]);
			ft_replace_env_by_value(expd->word, j, &(expd->expndd),
				&(expd->tmp));
		}
		else if (j == 0 || expd->word[*j - 1] != '$')
			ft_expnd_special_param_in_dble_g(expd->word, j,
				&(expd->expndd), last_env[0]);
		else
			ft_skip_char_non_env_var(expd->word, j,
				&(expd->expndd), 1);
	}
}

void	ft_expnd_backslashes_in_dble_qts(char *str, int *i, char **expndd)
{
	int		j;
	char	*tmp1;
	char	*tmp;

	j = *i;
	if (ft_strchr("$\"\\\n`", str[j + 1]))
	{
		tmp = *expndd;
		tmp1 = ft_substr(str, j + 1, 1);
		*expndd = ft_strjoin(*expndd, tmp1);
		j += 2;
		free(tmp);
		free(tmp1);
	}
	else
	{
		tmp = *expndd;
		tmp1 = ft_substr(str, j, 2);
		*expndd = ft_strjoin(*expndd, tmp1);
		j += 2;
		free(tmp);
		free(tmp1);
	}
	*i = j;
}

char	*ft_remove_double_quotes(char *word, int *i, t_env **env_list,
		char **last_env)
{
	t_expansion	expd;
	int			j;

	expd.expndd = NULL;
	j = *i + 1;
	expd.word = word;
	while (expd.word[j] != '"')
	{
		if (expd.word[j] == '\\')
			ft_expnd_backslashes_in_dble_qts(expd.word, &j, &expd.expndd);
		else
		{
			if (expd.word[j] == '$')
				ft_expnd_env_variable_in_dble_qte(&expd, &j, env_list,
					last_env);
			else
				ft_get_char(expd.word, &j, &expd.expndd);
		}
	}
	j++;
	*i = j;
	return (expd.expndd);
}

char	*ft_expnd_double_quotes(t_expansion expd, int *i, t_env **env_list,
		char **last_env)
{
	expd.tmp1 = expd.expndd;
	expd.tmp = ft_remove_double_quotes(expd.word, i, env_list, last_env);
	if (expd.tmp)
	{
		expd.expndd = ft_strjoin(expd.expndd, expd.tmp);
		free(expd.tmp);
		free(expd.tmp1);
	}
	return (expd.expndd);
}
