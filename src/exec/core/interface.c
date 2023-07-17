/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 00:40:54 by olimarti          #+#    #+#             */
/*   Updated: 2023/06/29 14:55:01 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "command.h"
#include "heredoc.h"

t_merror	exec_commands(t_vector *commands, t_vector *env)
{
	t_vector	converted_cmd;
	t_merror	result;

	result = exec_heredocs_layer(commands, env);
	return (result);
}
