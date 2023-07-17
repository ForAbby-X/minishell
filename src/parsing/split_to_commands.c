/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_to_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 00:52:45 by alde-fre          #+#    #+#             */
/*   Updated: 2023/07/17 17:23:59 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static inline t_merror	__split_redirs(
	t_token *const token,
	t_command *const command)
{
	char	*str;

	if (is_tok_operator(token))
		return (vector_addback(&command->redirs, token) == NULL);
	str = ft_strdup(token->data);
	return (vector_addback(&command->words, &str) == NULL);
}

t_merror	split_to_commands(t_vector *const tokens, t_vector *const commands)
{
	t_length	index;
	t_length	selected;
	t_command	*command;
	t_token		*token;

	index = 0;
	selected = 0;
	command = vector_addback(commands, &(t_command){0});
	if (command == NULL)
		return (MEMORY_ERROR);
	while (index < vector_size(tokens))
	{
		token = vector_get(tokens, index);
		if (token->type == PIPE)
		{
			command = vector_addback(commands, &(t_command){0});
			if (command == NULL)
				return (MEMORY_ERROR);
			selected++;
		}
		else if (__split_redirs(token, command))
			return (MEMORY_ERROR);
		index++;
	}
	return (SUCCESS);
}
