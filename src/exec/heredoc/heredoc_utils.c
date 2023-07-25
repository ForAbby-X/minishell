/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 23:19:12 by olimarti          #+#    #+#             */
/*   Updated: 2023/07/25 23:03:07 by olimarti         ###   ########.fr       */
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
	if (write(out_fd, "\n", 1) != 1)
		return (free(out_str), -1);
	free(out_str);
	return (0);
}

static inline void	__readline_clean(void)
{
	ft_putchar_fd('\n', STDIN_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
}

static int	_prompt(char *limiter, int out_fd, t_vector *env, int expandable)
{
	char	*line;
	int		limiter_len;

	errno = 0;
	line = readline("heredoc>");
	limiter_len = ft_strlen(limiter);
	while (line != 0 && !errno && (ft_strncmp(limiter, line, limiter_len) != 0
			|| line[limiter_len] != '\0'))
	{
		if (write_line(line, out_fd, env, expandable) != 0)
			return (free(line), 1);
		free(line);
		line = readline("heredoc>");
	}
	if (line == NULL && errno != 9)
		display_err("warning",
			(char *[])
		{"here-document delimited by end-of-file (wanted `",
			limiter, "')"}, 3);
	free(line);
	return (0);
}

t_merror	hd_prompt(char *limiter, int out_fd, t_vector *env, int expandable)
{
	int			tmp_fd;
	t_merror	err;

	err = SUCCESS;
	tmp_fd = dup(STDIN_FILENO);
	if (tmp_fd == -1)
		return (FAILURE);
	if (_prompt(limiter, out_fd, env, expandable))
		err = FAILURE;
	if (dup2(tmp_fd, STDIN_FILENO) == -1)
		return (close(tmp_fd), FATAL_ERROR);
	close(tmp_fd);
	if (errno == 9)
	{
		__readline_clean();
		return (FAILURE);
	}
	return (err);
}
