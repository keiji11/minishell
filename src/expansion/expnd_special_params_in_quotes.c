/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expnd_special_params_in_quotes.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llucente <llucente@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 16:05:53 by llucente          #+#    #+#             */
/*   Updated: 2021/08/31 15:32:17 by llucente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/execution.h"

void	get_dollar_sign(char *str, int *i, char **expndd)
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

void	ft_expnd_exit_status(int *i, char **expndd,
		char *exit_status)
{
	char	*tmp1;
	char	*tmp;

	tmp = exit_status;
	tmp1 = *expndd;
	*expndd = ft_strjoin(*expndd, tmp);
	free(tmp1);
	*i += 2;
}

void	ft_expnd_special_param_in_dble_g(char *str, int *i, char **expndd,
		char *exit_status)
{
	if (ft_isdigit(str[*i + 1])
		|| ft_strchr("!:#%@-*=/\\", str[*i + 1]))
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
	else if (str[*i + 1] && str[*i + 1] != '\"'
		&& str[*i + 1] != ' ')
		ft_skip_characters_env_not_exist(str, i);
	else
		get_dollar_sign(str, i, expndd);
}

void	ft_skip_char_non_env_var(char *str, int *i, char **expndd,
		int inside_quotes)
{
	char	*tmp1;
	char	*tmp;
	int		end_of_string;

	end_of_string = 0;
	tmp = NULL;
	tmp1 = NULL;
	end_of_string = check_end_of_string(str[*i + 1], inside_quotes);
	if (end_of_string)
	{
		tmp = *expndd;
		tmp1 = ft_substr(str, *i, 1);
		*expndd = ft_strjoin(*expndd, tmp1);
		free(tmp);
		free(tmp1);
		(*i)++;
	}
	else
		while (ft_isalpha(str[*i]) || str[*i] == '$')
			(*i)++;
}
