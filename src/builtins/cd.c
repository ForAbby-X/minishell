/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 12:39:37 by olimarti          #+#    #+#             */
/*   Updated: 2023/07/22 04:37:58 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins_cmd.h"
#include "utils.h"
#include "errno.h"
#include "env.h"

static inline t_merror	cd_err(char *str)
{
	ft_putstr_fd("cd: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	set_exit_code(1);
	return (FAILURE);
}

static t_merror	_set_env_vars(char *oldpwd, char *pwd, t_vector *env)
{
	oldpwd = ft_strjoin("OLDPWD=", oldpwd);
	if (!oldpwd)
		return (MEMORY_ERROR);
	printf("[%s]\n", oldpwd);
	set_env_var(oldpwd, ft_strchr(oldpwd, '='), env);
	free(oldpwd);
	pwd = ft_strjoin("PWD=", pwd);
	if (!pwd)
		return (MEMORY_ERROR);
	set_env_var(pwd, ft_strchr(pwd, '='), env);
	free(pwd);
	return (SUCCESS);
}

static t_merror	change_dir(char *path, t_vector *env)
{
	char		*tmp;
	t_merror	err;

	tmp = ft_getenv(env, "PWD");
	if (tmp == NULL)
		tmp = "";
	if (chdir(path) == -1)
		return (cd_err(strerror(errno)));
	path = getcwd(NULL, 0);
	if (!path)
		return (MEMORY_ERROR);
	err =_set_env_vars(tmp, path, env);
	free(path);
	return (err);
}

t_merror	builtin_cd(int argc, char **argv, t_vector *env)
{
	char		*path;
	t_merror	err;

	err = SUCCESS;
	if (argc > 2)
		err = cd_err("too many arguments");
	else if (argc == 2)
	{
		if (argv[1] != NULL && argv[1][0] != '\0')
			err = change_dir(argv[1], env);
	}
	else
	{
		path = ft_getenv(env, "HOME");
		if (path)
			err = change_dir(path, env);
		else
			err = cd_err("HOME not set");
	}
	if (err == SUCCESS)
		set_exit_code(0);
	return (err);
}
