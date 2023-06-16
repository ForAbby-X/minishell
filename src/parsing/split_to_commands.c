/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_to_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 00:52:45 by alde-fre          #+#    #+#             */
/*   Updated: 2023/06/16 13:20:30 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_merror	split_to_commands(t_vector *const tokens, t_vector *const commands)
{
	t_length	index;
	t_length	selected;
	t_command	*command;
	t_token		*token;

	index = 0;
	selected = 0;
	command = vector_addback(commands, &(t_command){0});
	while (index < vector_size(tokens))
	{
		token = vector_get(tokens, index);
		if (token->type == PIPE)
		{
			command = vector_addback(commands, &(t_command){0});
			selected++;
		}
		else
			vector_addback(&command->tokens, token);
		index++;
	}
	return (SUCCESS);
}
