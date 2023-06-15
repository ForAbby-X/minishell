/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 11:24:54 by alde-fre          #+#    #+#             */
/*   Updated: 2023/06/16 01:08:35 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

void	command_display(void *const object)
{
	t_command *const	command = object;

	printf("--Command--\ntokens: ");
	vector_for_each(&command->tokens, &token_display);
	printf("\nredirs : ");
	vector_for_each(&command->redirs, &redir_display);
	printf("\n");

}

t_merror	command_init(t_command *const command)
{
	command->tokens = vector_create(sizeof(t_token));
	if (command->tokens.buffer == NULL)
		return (MEMORY_ERROR);
	command->redirs = vector_create(sizeof(t_redir));
	if (command->redirs.buffer == NULL)
		return (vector_destroy(&command->tokens), MEMORY_ERROR);
	return (SUCCESS);
}

void	command_destroy(void *const object)
{
	t_command *const	command = object;

	vector_destroy(&command->tokens);
	vector_destroy(&command->redirs);
}

void	command_clear(void *const object)
{
	t_command *const	command = object;

	vector_for_each(&command->tokens, &token_destroy);
	vector_clear(&command->tokens);
	vector_for_each(&command->redirs, &redir_destroy);
	vector_clear(&command->redirs);
}
