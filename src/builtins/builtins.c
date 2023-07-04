/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 14:35:07 by olimarti          #+#    #+#             */
/*   Updated: 2023/07/05 01:06:02 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins_cmd.h"
#include "utils.h"

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
{NULL, NULL}
};

t_builtin_cmd_ptr	get_builtin_cmd(char *name)
{
	int	i;

	i = 0;
	if (name == NULL)
		return (NULL);
	while (g_builtins_list[i].name != NULL
		&& ft_strcmp(name, g_builtins_list[i].name) != 0)
	{
		i++;
	}
	return (g_builtins_list[i].func);
}
