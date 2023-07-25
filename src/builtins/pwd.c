/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 12:39:37 by olimarti          #+#    #+#             */
/*   Updated: 2023/07/25 02:48:54 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins_cmd.h"
#include "utils.h"
#include "errno.h"
#include "env.h"

t_merror	builtin_pwd(int argc, char **argv, t_vector *env)
{
	char	*path;

	(void) env;
	(void) argv;
	(void) argc;
	path = getcwd(NULL, 0);
	if (path == NULL)
	{
		_set_err("pwd", (char *[]){"error retrieving current directory: ",
			strerror(errno)}, 2, 0);
		return (FAILURE);
	}
	if (ft_putstrendl_fd_check(path, STDOUT_FILENO))
	{
		_set_err("pwd",
			(char*[]){"write error: ", strerror(errno)}, 2, 1);
		free(path);
		return (FAILURE);
	}
	set_exit_code(0);
	free(path);
	return (SUCCESS);
}
