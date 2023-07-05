/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 03:22:31 by alde-fre          #+#    #+#             */
/*   Updated: 2023/06/30 19:08:50 by alde-fre         ###   ########.fr       */
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

t_merror	pars_error(char *const str);
t_merror	check_tok_error(t_vector *const tokens);

int			is_expand_except(char const c);
//fuck this function, did it only because of missing room
t_merror	expand_exceptions(
				t_vector *const tokens,
				t_length *const index,
				char **const str);
t_merror	expand_token(
				t_vector *const tokens,
				t_length *const index,
				t_token *const token,
				t_vector const *const env);

t_merror	parser(
				char const *const line,
				t_vector *const commands,
				t_vector const *const env);
t_merror	lexer(char const *const line, t_vector *const tokens);
t_merror	merge_all_alpha(t_vector *const tokens);
t_merror	merge_redirs(t_vector *const tokens);
t_merror	split_to_commands(t_vector *const tokens, t_vector *const commands);

#endif
