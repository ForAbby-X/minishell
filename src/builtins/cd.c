/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 12:39:37 by olimarti          #+#    #+#             */
/*   Updated: 2023/07/26 06:50:12 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins_cmd.h"
#include "utils.h"
#include "errno.h"
#include "env.h"

static inline t_merror	__cd_err(char *str)
{
	set_err("cd", (char *[]){str}, 1, 1);
	return (FAILURE);
}

static t_merror	_set_env_vars(char *oldpwd, char *pwd, t_vector *env)
{
	oldpwd = ft_strjoin("OLDPWD=", oldpwd);
	if (!oldpwd)
		return (MEMORY_ERROR);
	pwd = ft_strjoin("PWD=", pwd);
	if (!pwd)
		return (free(oldpwd), MEMORY_ERROR);
	set_env_var(oldpwd, ft_strchr(oldpwd, '='), env);
	set_env_var(pwd, ft_strchr(pwd, '='), env);
	free(oldpwd);
	free(pwd);
	return (SUCCESS);
}

static t_merror	_change_dir(char *path, t_vector *env)
{
	char		*tmp;
	char		*new_pwd;
	t_merror	err;

	tmp = ft_getenv(env, "PWD");
	if (tmp == NULL)
		tmp = "";
	if (chdir(path) == -1)
	{
		set_err("cd", (char *[]){path, ": ", strerror(errno)}, 3, 1);
		return (FAILURE);
	}
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
	{
		set_err("cd", (char *[]){"error retrieving current directory: ",
			strerror(errno)}, 2, 1);
		_set_env_vars(tmp, path, env);
		return (FAILURE);
	}
	err = _set_env_vars(tmp, new_pwd, env);
	free(new_pwd);
	return (err);
}

static t_merror	go_oldpwd(t_vector *env)
{
	char		*path;
	t_merror	err;

	path = ft_getenv(env, "OLDPWD");
	if (path)
		err = _change_dir(path, env);
	else
		err = __cd_err("OLDPWD not set");
	path = ft_getenv(env, "PWD");
	if (err == SUCCESS && path && ft_putstrendl_fd_check(path, STDOUT_FILENO))
	{
		set_err("cd",
			(char*[]){"write error: ", strerror(errno)}, 2, 1);
		err = FAILURE;
	}
	return (err);
}

t_merror	builtin_cd(int argc, char **argv, t_vector *env)
{
	char		*path;
	t_merror	err;

	err = SUCCESS;
	if (argc > 2)
		err = __cd_err("too many arguments");
	else if (argc == 2)
	{
		if (argv[1] != NULL && ft_strcmp(argv[1], "-") == 0)
			err = go_oldpwd(env);
		else if (argv[1] != NULL && argv[1][0] != '\0')
			err = _change_dir(argv[1], env);
	}
	else
	{
		path = ft_getenv(env, "HOME");
		if (path)
			err = _change_dir(path, env);
		else
			err = __cd_err("HOME not set");
	}
	if (err != SUCCESS)
		return (FAILURE);
	set_exit_code(0);
	return (SUCCESS);
}
