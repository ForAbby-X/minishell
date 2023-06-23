/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 11:24:54 by alde-fre          #+#    #+#             */
/*   Updated: 2023/06/24 00:39:10 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

void	command_display(void *const object)
{
	t_command *const	command = object;

	printf("--Command--\ntokens: ");
	vector_for_each(&command->tokens, &token_display);
	printf("\nredirs : ");
	vector_for_each(&command->redirs, &token_display);
	printf("\n");
}

t_merror	command_init(t_command *const command)
{
	command->tokens = vector_create(sizeof(t_token));
	if (command->tokens.buffer == NULL)
		return (MEMORY_ERROR);
	vector_set_copy_method(&command->tokens, &token_cpy);
	command->redirs = vector_create(sizeof(t_token));
	if (command->redirs.buffer == NULL)
		return (vector_destroy(&command->tokens), MEMORY_ERROR);
	vector_set_copy_method(&command->redirs, &token_cpy);
	return (SUCCESS);
}

void	*command_cpy(void *dest, void *src, t_length const len)
{
	t_command *const	dest1 = dest;
	t_command *const	src1 = src;

	(void)len;
	*dest1 = *src1;
	command_init(dest1);
	return (dest1);
}

void	command_destroy(void *const object)
{
	t_command *const	command = object;

	vector_for_each(&command->tokens, token_destroy);
	vector_destroy(&command->tokens);
	vector_for_each(&command->redirs, token_destroy);
	vector_destroy(&command->redirs);
}

void	command_clear(void *const object)
{
	t_command *const	command = object;

	vector_for_each(&command->tokens, &token_destroy);
	vector_clear(&command->tokens);
	vector_for_each(&command->redirs, &token_destroy);
	vector_clear(&command->redirs);
}
