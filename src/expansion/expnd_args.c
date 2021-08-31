/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expnd_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llucente <llucente@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 16:03:27 by llucente          #+#    #+#             */
/*   Updated: 2021/08/31 15:32:17 by llucente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/execution.h"

void	ft_handle_arg_expnding(t_args **args)
{
	char	**splited;
	t_args	*tmp;
	t_args	*next;
	int		i;

	i = 0;
	splited = ft_split((*args)->value, ' ');
	tmp = *args;
	next = (*args)->next;
	free((*args)->value);
	while (splited[i])
	{
		tmp->value = splited[i];
		tmp->inside_quotes = 0;
		tmp->next = NULL;
		if (splited[i + 1])
		{
			tmp->next = (t_args *)malloc(sizeof(t_args));
			tmp = tmp->next;
		}
		i++;
	}
	tmp->next = next;
	free(splited);
}

t_args	*ft_expnd_argument(char *befor_expnd_arg, char	*after_expnd_arg,
		t_args *args)
{
	t_args	*next_args;
	char	*space;

	if (args->value)
		after_expnd_arg = ft_strdup(args->value);
	if (args->inside_quotes == 0 && after_expnd_arg
		&& ft_strcmp(befor_expnd_arg, after_expnd_arg)
		&& ft_strchr(after_expnd_arg, ' ')
		&& ft_strchr(befor_expnd_arg, '$'))
	{
		next_args = args->next;
		space = ft_strchr(after_expnd_arg, ' ');
		if (++space)
			ft_handle_arg_expnding(&args);
		args = next_args;
	}
	else
		args = args->next;
	free(after_expnd_arg);
	return (args);
}

void	ft_expnd_arguments(t_simple_cmd **cmd, t_env **env, char **last_env)
{
	t_args			*args;
	char			*befor_expnd_arg;
	char			*after_expnd_arg;

	args = (*cmd)->args;
	befor_expnd_arg = NULL;
	after_expnd_arg = NULL;
	while (args)
	{
		befor_expnd_arg = ft_strdup(args->value);
		ft_replace_space_by_tab(cmd, 0);
		args->inside_quotes = check_exiting_of_quotes(args->value);
		ft_expnd_word(&args->value, env, last_env, 0);
		args = ft_expnd_argument(befor_expnd_arg, after_expnd_arg, args);
		free(befor_expnd_arg);
		befor_expnd_arg = NULL;
		after_expnd_arg = NULL;
	}
}
