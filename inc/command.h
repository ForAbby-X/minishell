/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 11:22:43 by alde-fre          #+#    #+#             */
/*   Updated: 2023/06/14 20:43:46 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include "vector.h"
# include "error.h"
# include "token.h"
# include "redirs.h"

typedef struct s_command
{
	t_vector		tokens;
	t_vector		redirs;
}	t_command;

void		command_display(void *const object);
t_merror	command_init(t_command *const command);
void		command_destroy(void *const object);
void		command_clear(void *const object);

#endif
