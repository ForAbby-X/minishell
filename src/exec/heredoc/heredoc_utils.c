/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 23:19:12 by olimarti          #+#    #+#             */
/*   Updated: 2023/07/24 02:54:59 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"

static t_merror
	write_line(char *line, int out_fd, t_vector *env, int expandable)
{
	char	*out_str;
	int		line_len;

	out_str = NULL;
	if (expandable)
	{
		string_expander(line, &out_str, env);
		line = out_str;
	}
	line_len = ft_strlen(line);
	if (write(out_fd, line, line_len) != line_len)
		return (free(out_str), -1);
	free(out_str);
	return (0);
}

int	hd_prompt(char *limiter, int out_fd, t_vector *env, int expandable)
{
	char	*line;
	int		limiter_len;

	ft_putstr_fd("heredoc>", 0);
	errno = 0;
	line = get_next_line(STDIN_FILENO);
	limiter_len = ft_strlen(limiter);
	while (line != 0 && !errno && (ft_strncmp(limiter, line, limiter_len) != 0
			|| line[limiter_len] != '\n'))
	{
		ft_putstr_fd("heredoc>", 0);
		if (write_line(line, out_fd, env, expandable) != 0)
			return (free(line), -1);
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	free(line);
	return (errno);
}
