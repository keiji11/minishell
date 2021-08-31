/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expnd_special_params.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llucente <llucente@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 16:05:59 by llucente          #+#    #+#             */
/*   Updated: 2021/08/31 15:32:17 by llucente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/execution.h"

void	ft_expnd_rest_of_specail_params(char *str, int *i, char **expndd)
{
	char	*tmp1;
	char	*tmp;

	tmp1 = *expndd;
	tmp = ft_substr(str, *i, 2);
	*expndd = ft_strjoin(*expndd, tmp);
	free(tmp1);
	free(tmp);
}

void	ft_expnd_other_special_params(char *str, int *i, char **expndd)
{
	char	*tmp1;
	char	*tmp;

	if (str[*i + 1] == '#')
	{
		tmp1 = *expndd;
		tmp = ft_strdup("0");
		*expndd = ft_strjoin(*expndd, tmp);
		free(tmp1);
		free(tmp);
	}
	else if (str[*i + 1] == '-')
	{
		tmp1 = *expndd;
		tmp = ft_strdup("himBH");
		*expndd = ft_strjoin(*expndd, tmp);
		free(tmp1);
		free(tmp);
	}
	else if (ft_strchr(":%=/!", str[*i + 1]))
		ft_expnd_rest_of_specail_params(str, i, expndd);
	*i += 2;
}

void	ft_expnd_back_slash(int *i, char **expndd)
{
	char	*tmp1;
	char	*tmp;

	tmp1 = *expndd;
	tmp = ft_strdup("$");
	*expndd = ft_strjoin(*expndd, tmp);
	free(tmp1);
	free(tmp);
	(*i)++;
}

void	ft_digit_env(char *str, int *i, char **expndd)
{
	char	*tmp1;
	char	*tmp;

	if (str[*i + 1] == '0')
	{
		tmp1 = *expndd;
		tmp = ft_strdup("minishell");
		*expndd = ft_strjoin(*expndd, tmp);
		free(tmp1);
		free(tmp);
	}
	*i += 2;
}

void	ft_expnd_special_params(char *str, int *i, char **expndd,
		char *exit_status)
{
	if (str[*i + 1] != '"')
	{
		if (str[*i + 1] && (ft_isdigit(str[*i + 1])
				|| ft_strchr("!:#%@-*=/\\", str[*i + 1])))
		{
			if (ft_isdigit(str[*i + 1]))
				ft_digit_env(str, i, expndd);
			else if (ft_strchr("\\", str[*i + 1]))
				ft_expnd_back_slash(i, expndd);
			else
				ft_expnd_other_special_params(str, i, expndd);
		}
		else if (str[*i + 1] == '?')
			ft_expnd_exit_status(i, expndd, exit_status);
		else if (str[*i + 1])
			ft_skip_characters_env_not_exist(str, i);
		else
			get_dollar_sign(str, i, expndd);
	}
	else
		(*i)++;
}
