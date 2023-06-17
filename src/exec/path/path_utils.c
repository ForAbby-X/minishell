/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 12:24:24 by olimarti          #+#    #+#             */
/*   Updated: 2023/05/09 01:12:21 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	**parse_paths(char *path_str)
{
	char	**paths;

	paths = ft_split(path_str, ':');
	return (paths);
}

char	*join_path(char *dir, char *prog_name)
{
	int		dir_len;
	int		prog_name_len;
	char	*result;
	int		need_sep;

	if (!dir || !prog_name)
		return (NULL);
	dir_len = ft_strlen(dir);
	prog_name_len = ft_strlen(prog_name);
	if (dir_len == 0 || prog_name_len == 0)
		return (NULL);
	need_sep = (dir[dir_len - 1] != '/');
	result = malloc(sizeof(char) * (need_sep + dir_len + prog_name_len + 1));
	if (result == NULL)
		return (NULL);
	ft_strlcpy(result, dir, dir_len + 1);
	ft_strcpy(result + (dir_len + need_sep), prog_name);
	if (need_sep)
		result[dir_len] = '/';
	result[need_sep + dir_len + prog_name_len] = 0;
	return (result);
}
