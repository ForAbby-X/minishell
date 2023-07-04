/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 00:35:44 by olimarti          #+#    #+#             */
/*   Updated: 2023/06/29 15:05:41 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_HANDLERS_H
# define SIGNAL_HANDLERS_H
# define _XOPEN_SOURCE 500

# include "error.h"
# include "libft.h"

# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <signal.h>
# include <stddef.h>

void	set_ignore_signal_handlers(void);
void	set_prompt_signal_handlers(void);
void	restore_default_signal_handlers(void);
void	set_hd_signal_handlers(void);

void	prompt_on_sigint(int sig);
void	hd_on_sigint(int sig);

#endif
