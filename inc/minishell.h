/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 19:53:42 by alde-fre          #+#    #+#             */
/*   Updated: 2023/06/16 17:20:11 by olimarti         ###   ########.fr       */
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
# include "env.h"
# include "libft.h"

typedef struct s_minishell
{
	t_vector		tokens;
	//t_vector		redirs; @TO ADD
	char			**argv;
	int				argc;
	t_vector		env;
}	t_minishell;

#endif
