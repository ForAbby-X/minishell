/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 03:34:10 by olimarti          #+#    #+#             */
/*   Updated: 2023/06/26 05:46:50 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

# include "error.h"
# include "token.h"
# include "exec.h"
# include "libft.h"

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>

# define HEREDOC_PREFIX "minishell_hd"

t_merror	heredoc_file(char *limiter, char **filename);
// int	heredoc(char *limiter, char **filename);

t_merror	exec_heredocs_layer(t_vector *commands, t_vector *env);


#endif
