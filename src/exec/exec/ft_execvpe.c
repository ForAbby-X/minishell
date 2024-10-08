/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execvpe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:46:44 by olimarti          #+#    #+#             */
/*   Updated: 2023/07/05 00:48:54 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ft_execvpe(char *file, t_vector *argv, t_vector *const env)
{
	char	*path;

	if (file == NULL)
	{
		errno = 14;
		return (-3);
	}
	path = get_command_path(file, env);
	if (path == NULL)
	{
		errno = 2;
		return (-2);
	}
	else
		execve(path, argv->data, env->data);
	free(path);
	return (-1);
}
