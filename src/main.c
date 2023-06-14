/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 19:51:58 by alde-fre          #+#    #+#             */
/*   Updated: 2023/06/14 21:08:04 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline t_merror	__init_env(char **env, t_vector *const vector)
{
	while (*env)
	{
		if (vector_addback(vector, env) == NULL)
			return (MEMORY_ERROR);
		env++;
	}
	vector_addback(vector, &(char *){0});
	return (SUCCESS);
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
	minishell->argc = argc;
	minishell->argv = argv;
	minishell->env = vector_create(sizeof(char *));
	if (minishell->env.buffer == NULL)
		return (command_destroy(&minishell->commands), MEMORY_ERROR);
	if (__init_env(env, &minishell->env))
		return (command_destroy(&minishell->commands),
			vector_destroy(&minishell->env), MEMORY_ERROR);
	return (SUCCESS);
}

static inline t_merror	__launch_minishell(t_minishell *const minishell)
{
	char		*line;
	t_merror	error;

	error = SUCCESS;
	while (error == SUCCESS || error == PARSING_ERROR)
	{
		line = readline("minishell$ ");
		if (line && line[0])
		{
			add_history(line);
			error = parser(line, &minishell->commands);
			if (error == SUCCESS)
				vector_for_each(&minishell->commands, &command_display);
			else if (error == PARSING_ERROR)
				printf("PARSING ERROR\n");
		}
		vector_for_each(&minishell->commands, &command_clear);
		free(line);
		if (line == NULL)
			break ;
	}
	return (error);
}

static inline void	__destroy_minishell(t_minishell *const minishell)
{
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
	t_merror	error;

	if (!isatty(0) || __init_minishell(&minishell, argc, argv, env))
		return (1);
	error = __launch_minishell(&minishell);
	if (error == SUCCESS)
		__destroy_minishell(&minishell);
	return (error);
}
