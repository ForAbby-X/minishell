/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:45:19 by olimarti          #+#    #+#             */
/*   Updated: 2023/06/22 01:22:15 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	free_str_lst(char ***str_lst)
{
	char	**tmp_ptr;

	if (str_lst != NULL && *str_lst != NULL)
	{
		tmp_ptr = *str_lst;
		while (*tmp_ptr)
		{
			free(*tmp_ptr);
			tmp_ptr ++;
		}
		free(*str_lst);
		*str_lst = NULL;
	}
}


static char	*search_file_path(char *file, char **path_list)
{
	char	*path;

	path = NULL;
	if (path_list == NULL)
		return (NULL);
	while (*path_list != NULL)
	{
		path = join_path(*path_list, file);
		if (access(path, F_OK) == 0)
		{
			return (path);
		}
		free(path);
		path_list ++;
	}
	return (NULL);
}

char	*get_command_path(char *file, t_vector *const env)
{
	char	*paths_str;
	char	**path_list;
	char	*path;

	if (ft_strchr(file, '/'))
	{
		return (ft_strdup(file));
	}
	paths_str = ft_getenv(env, "PATH");
	path = NULL;
	if (paths_str == NULL)
		return (NULL);
	path_list = parse_paths(paths_str);
	path = search_file_path(file, path_list);
	free(paths_str);
	free_str_lst(&path_list);
	return (path);
}
