/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 19:51:58 by alde-fre          #+#    #+#             */
/*   Updated: 2023/07/26 09:46:08 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"
#include "signal_handlers.h"

#define COLOR_NC "\e[0m"
#define COLOR_BLACK "\e[0;30m"
#define COLOR_GRAY "\e[1;30m"
#define COLOR_RED "\e[0;31m"
#define COLOR_LIGHT_RED "\e[1;31m"
#define COLOR_GREEN "\e[0;32m"
#define COLOR_LIGHT_GREEN "\e[1;32m"
#define COLOR_BROWN "\e[0;33m"
#define COLOR_YELLOW "\e[1;33m"
#define COLOR_BLUE "\e[0;34m"
#define COLOR_LIGHT_BLUE "\e[1;34m"
#define COLOR_PURPLE "\e[0;35m"
#define COLOR_LIGHT_PURPLE "\e[1;35m"
#define COLOR_CYAN "\e[0;36m"
#define COLOR_LIGHT_CYAN "\e[1;36m"
#define COLOR_LIGHT_GRAY "\e[0;37m"
#define COLOR_WHITE "\e[1;37m"

static inline char	*minishell_prompt(void)
{
	char	*prompt;
	char	*pwd;
	char	*dir;
	char	*line;

	pwd = getcwd(NULL, 0);
	dir = "./";
	if (pwd)
		dir = ft_strrchr(pwd, '/') + 1;
	if (dir == NULL)
		dir = "./";
	prompt = multi_strjoin((char *[]){"\001", COLOR_WHITE, "\002", dir,
			"\001", COLOR_LIGHT_BLUE, "\002",
			" ~ ", "\001", COLOR_NC, "\002",}, 11);
	free(pwd);
	line = readline(prompt);
	free(prompt);
	return (line);
}

static inline t_merror	__init_minishell(
	t_minishell *const minishell,
	int argc,
	char **argv,
	char **env)
{
	minishell->commands = vector_create(sizeof(t_command));
	if (minishell->commands.buffer == NULL)
		return (MEMORY_ERROR);
	vector_set_copy_method(&minishell->commands, &command_cpy);
	minishell->argc = argc;
	minishell->argv = argv;
	minishell->env = vector_create(sizeof(char *));
	if (minishell->env.buffer == NULL)
		return (vector_destroy(&minishell->commands), MEMORY_ERROR);
	if (_init_env(env, &minishell->env))
		return (vector_destroy(&minishell->commands),
			vector_destroy(&minishell->env), MEMORY_ERROR);
	rl_outstream = stderr;
	return (SUCCESS);
}

static inline t_merror	__launch_minishell(t_minishell *const minishell)
{
	char		*line;
	t_merror	error;

	error = SUCCESS;
	while (error == SUCCESS || error == PARSING_ERROR || error == FAILURE)
	{
		set_prompt_signal_handlers();
		line = minishell_prompt();
		if (line && line[0])
		{
			add_history(line);
			error = parser(line, &minishell->commands, &minishell->env);
			if (error == SUCCESS)
				error |= exec_commands(&(minishell->commands),
						&(minishell->env));
		}
		vector_for_each(&minishell->commands, &command_destroy);
		vector_clear(&minishell->commands);
		free(line);
		if (line == NULL)
			break ;
	}
	return (SUCCESS);
}

static inline void	__destroy_minishell(t_minishell *const minishell)
{
	_env_destroy(&minishell->env);
	vector_destroy(&minishell->env);
	vector_for_each(&minishell->commands, &command_destroy);
	vector_destroy(&minishell->commands);
	rl_clear_history();
}

int	main(
	int argc,
	char **argv,
	char **env)
{
	t_minishell	minishell;

	if (!isatty(STDIN_FILENO) || __init_minishell(&minishell, argc, argv, env))
		return (1);
	__launch_minishell(&minishell);
	__destroy_minishell(&minishell);
	return (get_exit_code());
}
