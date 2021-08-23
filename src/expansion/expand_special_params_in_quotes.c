/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_special_params_in_quotes.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llucente <llucente@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 16:05:53 by llucente          #+#    #+#             */
/*   Updated: 2021/08/23 16:05:54 by llucente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/execution.h"

void	get_dollar_sign(char *str, int *i, char **expanded)
{
	char	*tmp1;
	char	*tmp;

	tmp1 = *expanded;
	tmp = ft_substr(str, *i, 1);
	*expanded = ft_strjoin(*expanded, tmp);
	free(tmp1);
	free(tmp);
	(*i)++;
}

void	ft_expand_exit_status(int *i, char **expanded,
		char *exit_status)
{
	char	*tmp1;
	char	*tmp;

	tmp = exit_status;
	tmp1 = *expanded;
	*expanded = ft_strjoin(*expanded, tmp);
	free(tmp1);
	*i += 2;
}

void	ft_expande_special_param_in_dble_g(char *str, int *i, char **expanded,
		char *exit_status)
{
	if (ft_isdigit(str[*i + 1])
		|| ft_strchr("!:#%@-*=/\\", str[*i + 1]))
	{
		if (ft_isdigit(str[*i + 1]))
			ft_digit_env(str, i, expanded);
		else if (ft_strchr("\\", str[*i + 1]))
			ft_expand_back_slash(i, expanded);
		else
			ft_expand_other_special_params(str, i, expanded);
	}
	else if (str[*i + 1] == '?')
		ft_expand_exit_status(i, expanded, exit_status);
	else if (str[*i + 1] && str[*i + 1] != '\"'
		&& str[*i + 1] != ' ')
		ft_skip_characters_env_not_exist(str, i);
	else
		get_dollar_sign(str, i, expanded);
}

void	ft_skip_characters_non_env_variable(char *str, int *i, char **expanded,
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
		tmp = *expanded;
		tmp1 = ft_substr(str, *i, 1);
		*expanded = ft_strjoin(*expanded, tmp1);
		free(tmp);
		free(tmp1);
		(*i)++;
	}
	else
		while (ft_isalpha(str[*i]) || str[*i] == '$')
			(*i)++;
}
