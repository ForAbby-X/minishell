/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 20:36:27 by alde-fre          #+#    #+#             */
/*   Updated: 2023/06/16 23:10:45 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_vector	expand_token(t_token *const token)
{
	t_vector	sub;

	(void)token;
	sub = vector_create(sizeof(t_token));
	if (sub.data == NULL)
		return ((t_vector){0});
	if (lexer("alde-fre oui >oui je test tout", &sub))
	{
		vector_for_each(&sub, &token_destroy);
		return (vector_destroy(&sub), (t_vector){0});
	}
	return (sub);
}
