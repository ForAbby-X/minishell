/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 19:51:58 by alde-fre          #+#    #+#             */
/*   Updated: 2023/06/22 00:55:19 by olimarti         ###   ########.fr       */
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
	if (vector_addback(vector, env) == NULL)
		return (MEMORY_ERROR);
	return (SUCCESS);
}

static inline t_merror	__init_minishell(
	t_minishell *const minishell,
	int argc,
	char **argv,
	char **env)
{
	minishell->tokens = vector_create(sizeof(t_token));
	if (minishell->tokens.buffer == NULL)
		return (MEMORY_ERROR);
	minishell->argc = argc;
	minishell->argv = argv;
	minishell->env = vector_create(sizeof(char *));
	if (minishell->env.buffer == NULL)
		return (vector_destroy(&minishell->tokens), MEMORY_ERROR);
	if (__init_env(env, &minishell->env))
		return (vector_destroy(&minishell->tokens),
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
			error = lexer(line, &minishell->tokens);
			if (error == SUCCESS)
				vector_for_each(&minishell->tokens, &token_display);
			else if (error == PARSING_ERROR)
				printf("PARSING ERROR\n");
		}
		vector_for_each(&minishell->tokens, &token_destroy);
		vector_clear(&minishell->tokens);
		free(line);
		if (line == NULL)
			break ;
	}
	return (error);
}

static inline void	__destroy_minishell(t_minishell *const minishell)
{
	vector_destroy(&minishell->env);
	vector_destroy(&minishell->tokens);
	rl_clear_history();
}

// int	main(
// 	int argc,
// 	char **argv,
// 	char **env)
// {
// 	t_minishell	minishell;
// 	t_merror	error;

// 	if (!isatty(0) || __init_minishell(&minishell, argc, argv, env))
// 		return (1);
// 	error = __launch_minishell(&minishell);
// 	if (error == SUCCESS)
// 		__destroy_minishell(&minishell);
// 	return (error);
// }


t_exec_command fake_cmd()
{
	t_exec_command cmd;
	char *tmp;
	t_redir redir;

	exec_command_init(&cmd);
	// tmp = ft_strdup("ls");
	// vector_addback(&(cmd.args), &tmp);
	// tmp = ft_strdup("-l");
	// vector_addback(&(cmd.args), &tmp);
	// tmp = ft_strdup("-a");
	// vector_addback(&(cmd.args), &tmp);
	// tmp = NULL;
	// vector_addback(&(cmd.args), &tmp);
	tmp = ft_strdup("cat");
	vector_addback(&(cmd.args), &tmp);
	tmp = ft_strdup("-e");
	vector_addback(&(cmd.args), &tmp);
	tmp = NULL;
	vector_addback(&(cmd.args), &tmp);
	
	redir.path = ft_strdup("test.txt");
	redir.type = R_REDIR_IN;
	vector_addback(&(cmd.redirs), &redir);

	redir.path = ft_strdup("test2.txt");
	redir.type = R_APPEND;
	vector_addback(&(cmd.redirs), &redir);

	exec_command_display(&cmd);
	return (cmd);
}


int	main(
	int argc,
	char **argv,
	char **env)
{
	t_minishell		minishell;
	t_merror		error;
	t_exec_command	cmd;
	
	if (!isatty(0) || __init_minishell(&minishell, argc, argv, env))
		return (1);
	// error = __launch_minishell(&minishell);
	//tmp = ft_getenv(&minishell.env, "PATH");
	//	free(tmp);

	cmd = fake_cmd();
	exec_command_display(&cmd);
	run_command(&cmd, &(minishell.env));
	exec_command_destroy(&cmd);
	//vector_destroy(&tmp_args);
	error = SUCCESS;
	if (error == SUCCESS)
		__destroy_minishell(&minishell);
	return (error);
}

