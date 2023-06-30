/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_exceptions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 19:04:15 by alde-fre          #+#    #+#             */
/*   Updated: 2023/06/30 19:14:18 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// int	is_expand_except(char const c)
// {
// 	return (c == 0 || c == '$' || c == '?'
// 		|| ft_isdigit(c) || !(ft_isalnum(c) || c == '_'))
// }

// t_merror	expand_exceptions(
// 	t_vector *const tokens,
// 	t_length *const index,
// 	char **const str)
// {
// 	if (*ptr == 0)
// 		return (*str += 1, __expand_var_quoted(tokens, index, "$"));
// 	if (*ptr == '$')
// 		return (*str += 2, __expand_var_quoted(tokens, index, "PROCESS_PID"));
// 	if (*ptr == '?')
// 		return (*str += 2, __expand_var_quoted(tokens, index, "ERROR_CODE"));
// 	if (ft_isdigit(*ptr) || !(ft_isalnum(*ptr) || *ptr == '_'))
// 		return (*str += 2, tmp = *(ptr + 1), *(ptr + 1) = 0,
// 			__expand_var_quoted(tokens, index, ptr - 1), *(ptr + 1) = tmp, 0);
// 	return (SUCCESS);
// }
