/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_exceptions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 19:04:15 by alde-fre          #+#    #+#             */
/*   Updated: 2023/07/20 12:27:19 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "error.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

char	*ft_getpid(void)
{
	int		fd;
	int		err;
	char	tab[13];

	fd = open("/proc/self/stat", O_RDONLY);
	if (fd == -1)
		return (NULL);
	err = read(fd, tab, 13);
	if (err <= 0)
		return (close(fd), "");
	close(fd);
	*ft_strchr(tab, ' ') = '\0';
	return (ft_strdup(tab));
}

char	*exp_get_var(char const c)
{
	if (c == '\0')
		return (ft_strdup("$"));
	else if (c == '$')
		return (ft_getpid());
	else if (c == '?')
		return (ft_itoa(get_exit_code()));
	return (NULL);
}
