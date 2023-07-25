/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cmd.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 00:36:30 by olimarti          #+#    #+#             */
/*   Updated: 2023/07/25 03:30:11 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_CMD_H
# define BUILTINS_CMD_H

# include "error.h"
# include "vector.h"
# include "libft.h"
# include "command.h"

typedef t_merror			(*t_builtin_cmd_ptr)(int, char**, t_vector*);
typedef t_builtin_cmd_ptr	(*t_pm)();

t_merror			builtin_echo(int argc, char **argv, t_vector *env);
t_merror			builtin_exit(int argc, char **argv, t_vector *env);
t_merror			builtin_cd(int argc, char **argv, t_vector *env);
t_merror			builtin_pwd(int argc, char **argv, t_vector *env);
t_merror			builtin_env(int argc, char **argv, t_vector *env);
t_merror			builtin_unset(int argc, char **argv, t_vector *env);
t_merror			builtin_export(int argc, char **argv, t_vector *env);
t_merror			builtin_empty(int argc, char **argv, t_vector *env);

t_builtin_cmd_ptr	get_builtin_cmd(t_command *cmd);

#endif
