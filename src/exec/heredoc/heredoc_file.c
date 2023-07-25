/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 23:19:12 by olimarti          #+#    #+#             */
/*   Updated: 2023/07/21 18:52:02 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"

static char	*name_gen(char *directory, char *basename, int nb)
{
	char	*result;
	char	*nb_alpha;
	int		i;

	i = 0;
	nb_alpha = ft_itoa(nb);
	if (nb_alpha == NULL)
		return (NULL);
	result = malloc(sizeof(char) * (ft_strlen(directory) + ft_strlen(basename)
				+ ft_strlen(nb_alpha) + 2));
	i = ft_strcpyl(result + i, directory);
	result[i] = '/';
	i++;
	i += ft_strcpyl(result + i, basename);
	i += ft_strcpyl(result + i, nb_alpha);
	result[i] = '\0';
	free(nb_alpha);
	return (result);
}

static char	*heredoc_file_name(char *directory)
{
	int		i;
	char	*path;

	i = 0;
	if (access(directory, W_OK | R_OK) != 0)
		return (NULL);
	path = name_gen(directory, HEREDOC_PREFIX, i);
	while (access(path, F_OK) == 0)
	{
		free(path);
		path = NULL;
		if (i == (int)(0xFFFFFFFF >> 1))
			return (free(path), "/tmp/\"c la sose\"");
		free(path);
		path = name_gen(directory, HEREDOC_PREFIX, i);
		i++;
	}
	return (path);
}

static int	create_heredoc_file(int *fd, char **filepath)
{
	char	*path;

	*filepath = NULL;
	path = heredoc_file_name("/tmp");
	if (path == NULL)
		return (1);
	*fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (*fd == -1)
	{
		free(path);
		return (1);
	}
	*filepath = path;
	return (0);
}

t_merror
	heredoc_file(char *limiter, char **filename, t_vector *env, int expandable)
{
	int		fd;

	if (create_heredoc_file(&fd, filename) != 0)
	{
		perror("cannot open heredoc");
		return (FAILURE);
	}
	if (hd_prompt(limiter, fd, env, expandable) != 0)
	{
		close(fd);
		unlink(*filename);
		free(*filename);
		*filename = NULL;
		return (FAILURE);
	}
	close(fd);
	return (SUCCESS);
}
