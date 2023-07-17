/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 12:39:37 by olimarti          #+#    #+#             */
/*   Updated: 2023/07/04 17:38:38 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins_cmd.h"
#include "utils.h"
#include "errno.h"
#include "env.h"

static inline t_merror	cd_err(char *str)
{
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	set_exit_code(1);
	return (FAILURE);
}

t_merror	builtin_cd(int argc, char **argv, t_vector *env)
{
	char		*path;
	t_merror	err;

	err = SUCCESS;
	if (argc > 2)
		err = cd_err("cd: too many arguments");
	else if (argc == 2)
	{
		if (argv[1] == NULL || argv[1][0] == '\0')
			err = cd_err("cd: null directory");
		else
			chdir(argv[1]);
	}
	else
	{
		path = ft_getenv(env, "HOME");
		if (path)
			chdir(path);
		else
			err = cd_err("cd: HOME not set");
		free(path);
	}
	if (err == SUCCESS)
		set_exit_code(0);
	return (err);
}
