/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 12:39:37 by olimarti          #+#    #+#             */
/*   Updated: 2023/07/24 05:51:51 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins_cmd.h"
#include "utils.h"
#include "errno.h"
#include "env.h"

static char	*get_pwd(void)
{
	char		*path;
	size_t		size;

	errno = 0;
	size = 100;
	path = ft_calloc(size, sizeof(char));
	if (path == NULL)
		return (NULL);
	while (getcwd(path, size - 1) == NULL && errno == ERANGE)
	{
		free(path);
		size *= 2;
		path = ft_calloc(size, sizeof(char));
		if (path == NULL)
			return (NULL);
	}
	if (errno != 0 && errno != ERANGE)
	{
		free(path);
		return (NULL);
	}
	return (path);
}

t_merror	builtin_pwd(int argc, char **argv, t_vector *env)
{
	char	*path;

	(void) env;
	(void) argv;
	(void) argc;
	path = get_pwd();
	if (path == NULL)
	{
		ft_putstr_fd("pwd: error retrieving current directory\n", STDERR_FILENO);
		set_exit_code(1);
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
