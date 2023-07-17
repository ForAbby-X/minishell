/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 14:58:39 by olimarti          #+#    #+#             */
/*   Updated: 2023/06/29 15:18:33 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal_handlers.h"

void	prompt_on_sigint(int sig)
{
	(void) sig;
	ft_putchar_fd('\n', STDIN_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	set_exit_code(128 + sig);
}

void	hd_on_sigint(int sig)
{
	(void) sig;
	set_exit_code(128 + sig);
}
