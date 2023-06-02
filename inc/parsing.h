/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 03:22:31 by alde-fre          #+#    #+#             */
/*   Updated: 2023/05/30 20:39:57 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "error.h"
# include "token.h"

int			is_separator(char const c);
int			is_quotes(char const c);
int			is_operator(char const c);
int			ft_strncmp(char const *str0, char const *str1, size_t len);

void		pars_error(char *const str);

t_merror	lexer(char const *const line, t_vector *const tokens);

t_merror	parser(t_vector *const tokens);

#endif
