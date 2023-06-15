/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_to_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 00:52:45 by alde-fre          #+#    #+#             */
/*   Updated: 2023/06/16 01:20:02 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_merror	split_to_commands(t_vector *const tokens, t_vector *const commands)
{
	t_length	index;
	t_length	count;
	t_command	*command;
	t_token		*token;

	index = 0;
	count = 0;
	vector_resize(commands, 1);
	command_init(vector_get(commands, 0));
	while (index < vector_size(tokens))
	{
		command = vector_get(commands, count);
		token = tokens_get(tokens, index);
		if (token->type == PIPE)
		{
			command_init(vector_addback(commands, &(t_command){0}));
			count++;
		}
		else
			vector_addback(&command->tokens, token);
		index++;
	}
	return (SUCCESS);
}
