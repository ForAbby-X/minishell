/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 01:26:00 by olimarti          #+#    #+#             */
/*   Updated: 2023/07/26 08:01:55 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "libft.h"
#include "utils.h"

int	g_exit_code = 0;

void	set_exit_code(int exit_code)
{
	g_exit_code = exit_code;
}

int	get_exit_code(void)
{
	return (g_exit_code);
}

void	display_err(char *cmd, char **err, int count)
{
	char	*tmp;
	char	*tmp2;

	tmp2 = NULL;
	tmp = multi_strjoin(err, count);
	if (tmp)
		tmp2 = multi_strjoin((char *[]){"minishell: ", cmd, ": ", tmp, "\n"}, 5);
	if (tmp2)
		ft_putstr_fd(tmp2, STDERR_FILENO);
	else
		ft_putstr_fd("minishell: internal error", STDERR_FILENO);
	free(tmp);
	free(tmp2);
}

void	set_err(char *cmd, char **err, int count, int code)
{
	set_exit_code(code);
	display_err(cmd, err, count);
}
