/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 03:22:31 by alde-fre          #+#    #+#             */
/*   Updated: 2023/06/19 02:36:25 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "error.h"
# include "token.h"
# include "command.h"
# include "libft.h"

int			is_separator(char const c);
int			is_quotes(char const c);
int			is_operator(char const c);
int			is_tok_alpha(t_token const *const token);
int			is_tok_operator(t_token const *const token);

void		pars_error(char *const str);

t_merror	lexer_separator(
				char const *const line,
				t_length *const index,
				t_vector *const tokens);

t_merror	expand_token(
				t_vector *const tokens,
				t_length *const index,
				t_token *const token);

t_merror	parser(char const *const line, t_vector *const commands);
t_merror	lexer(char const *const line, t_vector *const tokens);
t_merror	merge_all_tokens(t_vector *const tokens);
t_merror	merge_redirs(t_vector *const tokens);
t_merror	split_to_commands(t_vector *const tokens, t_vector *const commands);

#endif

//CECI | EST | UN | TEST | OUI NON
