/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 14:35:07 by olimarti          #+#    #+#             */
/*   Updated: 2023/07/18 20:40:40 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins_cmd.h"
#include "utils.h"
#include "exec.h"
#include "stdio.h"

typedef struct s_builtin_map
{
	char				*name;
	t_builtin_cmd_ptr	func;
}	t_builtin_map;

static t_builtin_map const	g_builtins_list[] = {
{"", builtin_empty},
{"echo", builtin_echo},
{"exit", builtin_exit},
{"cd", builtin_cd},
{"pwd", builtin_pwd},
{"env", builtin_env},
{"unset", builtin_unset},
{"export", builtin_export},
{NULL, NULL}
};

t_builtin_cmd_ptr	get_builtin_cmd(t_command *cmd)
{
	int		i;
	char	*name;

	i = 0;
	if (!cmd)
		return (NULL);
	if (cmd->words.size == 0)
		return (builtin_empty);
	name = *((char **)cmd->words.data);
	if (name == NULL)
		return (builtin_empty);
	while (g_builtins_list[i].name != NULL
		&& ft_strcmp(name, g_builtins_list[i].name) != 0)
	{
		i++;
	}
	return (g_builtins_list[i].func);
}
