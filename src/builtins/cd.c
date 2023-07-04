/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 12:39:37 by olimarti          #+#    #+#             */
/*   Updated: 2023/07/04 16:32:11 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins_cmd.h"
#include "utils.h"
#include "errno.h"
#include "env.h"

t_merror	builtin_cd(int argc, char **argv, t_vector *env)
{
	char	*path;

	if (argc > 2)
	{
		ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO);
	}
	else if (argc == 2)
	{
		if (argv[1] == NULL || argv[1][0] == '\0')
			ft_putstr_fd("cd: null directory\n", STDERR_FILENO);
		else
			chdir(argv[1]);
	}
	else
	{
		path = ft_getenv(env, "HOME");
		if (path)
			chdir(path);
		else
			ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO);
	}
	set_exit_code(0);
	return (SUCCESS);
}
