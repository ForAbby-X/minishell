/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 11:24:54 by alde-fre          #+#    #+#             */
/*   Updated: 2023/06/28 19:26:49 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

void	command_display(void *const object)
{
	t_command *const	command = object;

	printf("--Command--\nwords: ");
	vector_for_each(&command->words, &word_display);
	printf("\nredirs : ");
	vector_for_each(&command->redirs, &token_display);
	printf("\n");
}

t_merror	command_init(t_command *const command)
{
	command->words = vector_create(sizeof(char *));
	if (command->words.buffer == NULL)
		return (MEMORY_ERROR);
	command->redirs = vector_create(sizeof(t_token));
	if (command->redirs.buffer == NULL)
		return (vector_destroy(&command->words), MEMORY_ERROR);
	vector_set_copy_method(&command->redirs, &token_cpy);
	return (SUCCESS);
}

void	*command_cpy(void *dest, void *src, t_length const len)
{
	t_command *const	dest1 = dest;
	t_command *const	src1 = src;

	(void)len;
	*dest1 = *src1;
	if (command_init(dest1))
		return (NULL);
	return (dest1);
}

void	command_destroy(void *const object)
{
	t_command *const	command = object;

	vector_for_each(&command->words, &word_destroy);
	vector_destroy(&command->words);
	vector_for_each(&command->redirs, &token_destroy);
	vector_destroy(&command->redirs);
}

void	command_clear(void *const object)
{
	t_command *const	command = object;

	vector_for_each(&command->words, &word_destroy);
	vector_clear(&command->words);
	vector_for_each(&command->redirs, &token_destroy);
	vector_clear(&command->redirs);
}
