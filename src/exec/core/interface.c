/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 00:40:54 by olimarti          #+#    #+#             */
/*   Updated: 2023/06/27 13:07:11 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "command.h"
#include "heredoc.h"

static void	custom_exec_command_destroy(void *const object)
{
	t_exec_command *const	command = object;

	vector_for_each(&command->args, &arg_destroy);
	vector_destroy(&command->args);
	vector_destroy(&command->redirs);
}

static t_merror
	command_to_exec_cmd(t_command *const command, t_exec_command *exec_cmd)
{
	t_length	i;
	char		*tmp;

	i = 0;
	if (exec_command_init(exec_cmd) != SUCCESS)
		return (MEMORY_ERROR);
	if (vector_reserve(&(exec_cmd->redirs), command->redirs.size) != 0)
		return (exec_command_destroy(exec_cmd), MEMORY_ERROR);
	vector_copy(&(exec_cmd->redirs), &(command->redirs));
	if (vector_reserve(&(exec_cmd->args), command->tokens.size) != 0)
		return (exec_command_destroy(exec_cmd), MEMORY_ERROR);
	while (i < command->tokens.size)
	{
		tmp = ft_strdup(((t_token *)vector_get(&(command->tokens), i))->data);
		if (tmp == NULL || vector_addback(&(exec_cmd->args), &tmp) == NULL)
		{
			free(tmp);
			exec_command_destroy(exec_cmd);
			return (MEMORY_ERROR);
		}
		i++;
	}
	vector_addback(&(exec_cmd->args), &(char *){0});
	return (SUCCESS);
}

static t_merror
	convert_vect_commands(t_vector *const commands, t_vector *exec_cmds)
{
	t_length		i;
	t_exec_command	tmp_cmd;

	*exec_cmds = vector_create(sizeof(t_exec_command));
	i = 0;
	while (i < commands->size)
	{
		if (command_to_exec_cmd(vector_get(commands, i), &tmp_cmd) != SUCCESS)
			return (vector_destroy(exec_cmds), MEMORY_ERROR);
		if (vector_addback(exec_cmds, &tmp_cmd) == NULL)
		{
			exec_command_destroy(&tmp_cmd);
			vector_destroy(exec_cmds);
			return (MEMORY_ERROR);
		}
		i++;
	}
	return (SUCCESS);
}

t_merror	exec_commands(t_vector *commands, t_vector *env)
{
	t_vector	converted_cmd;
	t_merror	result;

	if (convert_vect_commands(commands, &converted_cmd) != SUCCESS)
		return (MEMORY_ERROR);
	result = exec_heredocs_layer(&converted_cmd, env);
	vector_for_each(&converted_cmd, custom_exec_command_destroy);
	vector_destroy(&converted_cmd);
	return (result);
}
