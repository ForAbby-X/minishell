/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 01:26:00 by olimarti          #+#    #+#             */
/*   Updated: 2023/07/25 23:02:18 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "libft.h"
#include "utils.h"

int	g_exit_code = 0;

void	set_exit_code(int exit_code)
{
	g_exit_code = exit_code;
}

int	get_exit_code(void)
{
	return (g_exit_code);
}

static	char	*_multi_strjoin(char *tab[], int count)
{
	int		i;
	int		lenght;
	char	*str;

	i = 0;
	lenght = 0;
	while (i < count)
	{
		lenght += ft_strlen(tab[i]);
		i++;
	}
	str = malloc((lenght + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	lenght = 0;
	while (i < count)
	{
		lenght += ft_strcpyl(str + lenght, tab[i]);
		++i;
	}
	str[lenght] = 0;
	return (str);
}

void	display_err(char *cmd, char **err, int count)
{
	char	*tmp;
	char	*tmp2;

	tmp2 = NULL;
	tmp = _multi_strjoin(err, count);
	if (tmp)
		tmp2 = _multi_strjoin((char *[]){"bash: ", cmd, ": ", tmp, "\n"}, 5);
	if (tmp2)
		ft_putstr_fd(tmp2, STDERR_FILENO);
	else
		ft_putstr_fd("bash: internal error", STDERR_FILENO);
	free(tmp);
	free(tmp2);
}

void	set_err(char *cmd, char **err, int count, int code)
{
	set_exit_code(code);
	display_err(cmd, err, count);
}
