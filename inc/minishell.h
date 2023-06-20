/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 19:53:42 by alde-fre          #+#    #+#             */
/*   Updated: 2023/06/20 20:11:13 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "vector.h"
# include "error.h"
# include "token.h"
# include "command.h"
# include "parsing.h"

typedef struct s_minishell
{
	t_vector		commands;
	char			**argv;
	int				argc;
	t_vector		env;
}	t_minishell;

#endif
