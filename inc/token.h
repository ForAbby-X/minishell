/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 02:26:36 by alde-fre          #+#    #+#             */
/*   Updated: 2023/05/24 17:13:41 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "vector.h"

typedef enum e_type_token {
	BLANK,
	WORD,
	NAME,
	METACHAR,
	OPERATOR,
	SINGLE_QUOTED,
	DOUBLE_QUOTED
}	t_ttoken;

typedef struct s_token
{
	char		*data;
	t_ttoken	type;
}	t_token;

void	token_display(void *const object);
void	token_destroy(void *const object);
t_token	*tokens_add(t_vector *const vector, t_token	*const obj)
		__attribute__((always_inline));
t_token	*tokens_get(t_vector *const vector, t_length const index)
		__attribute__((always_inline));

#endif
