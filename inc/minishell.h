/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 19:53:42 by alde-fre          #+#    #+#             */
/*   Updated: 2023/05/24 18:18:55 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "error.h"
# include "token.h"
# include "vector.h"
# include "parsing.h"

typedef char *	*t_arguments;

typedef struct s_minishell
{
	t_vector		tokens;
	t_arguments		argv;
	int				argc;
	t_vector		env;
}	t_minishell;

#endif
