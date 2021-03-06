/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llucente <llucente@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 16:10:22 by llucente          #+#    #+#             */
/*   Updated: 2021/08/31 15:32:30 by llucente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include "../headers/execution.h"

void	ft_tkn_n_pars(char **line, t_pipe_line **current_pipe_line, int *status)
{
	t_token		*tkns_list;

	tkns_list = NULL;
	if (*line)
	{
		tkns_list = ft_lexer(*line);
		free(*line);
		*line = NULL;
	}
	if (tkns_list)
	{
		g_vars.cmd = ft_parser(tkns_list, status);
		tkns_list = NULL;
	}
	if (g_vars.cmd)
		*current_pipe_line = g_vars.cmd->childs;
}

int	ft_exp_n_exe_pipe_line(t_pipe_line *current_pipe_line,
		char **last_arg_exit_sts, int *status, t_env **env_list)
{
	if (last_arg_exit_sts[0])
		free(last_arg_exit_sts[0]);
	last_arg_exit_sts[0] = ft_int_to_string(*status);
	ft_expnding(current_pipe_line, env_list, last_arg_exit_sts);
	current_pipe_line->child = ft_del_empty_simple_cmds(&current_pipe_line);
	if (current_pipe_line->child)
	{
		if (last_arg_exit_sts[1])
			free(last_arg_exit_sts[1]);
		last_arg_exit_sts[1] = get_lst_arg_or_cmds(current_pipe_line);
		*status = ft_execute(current_pipe_line, env_list);
	}
	return (*status);
}

void	ft_init_minishell(char	**lst_arg_exit_status, char **line,
		t_pipe_line **current_pipe_line, t_env **env_list)
{
	g_vars.cmd = NULL;
	*current_pipe_line = NULL;
	lst_arg_exit_status[0] = ft_strdup("0");
	*line = NULL;
	*env_list = NULL;
}

void	ft_destroy_main_ast(void)
{
	if (g_vars.cmd)
	{
		ft_destroy_ast(g_vars.cmd);
		ft_putstr_fd(RESET, ft_strlen(RESET));
		g_vars.cmd = NULL;
	}
}

void	ft_minishell(char **env)
{
	t_pipe_line	*currnt_pipe_line;
	t_env		*env_list;
	char		*line;
	int			status;
	static char	*lst_arg_exit_status[2];

	status = 0;
	ft_init_minishell(lst_arg_exit_status, &line, &currnt_pipe_line, &env_list);
	signal(SIGINT, ft_signal_handler);
	signal(SIGQUIT, ft_signal_handler);
	ft_init_env(&env_list, env);
	while (1337)
	{
		show_prompt();
		micro_read_line(&line, &status);
		ft_tkn_n_pars(&line, &currnt_pipe_line, &status);
		while (currnt_pipe_line)
		{
			status = ft_exp_n_exe_pipe_line(currnt_pipe_line,
					lst_arg_exit_status, &status, &env_list);
			currnt_pipe_line = currnt_pipe_line->next;
		}
		ft_destroy_main_ast();
	}
	ft_destroy_env_list(env_list);
}
