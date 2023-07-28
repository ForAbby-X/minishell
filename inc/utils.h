/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 02:26:36 by alde-fre          #+#    #+#             */
/*   Updated: 2023/07/26 03:18:36 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>

char	*ft_getpid(void);
int		ft_strcpyl(char *dst, char *src);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_atoi_validate(char *str, int *result);
int		legal_number(char *str, int *result);
int		ft_putstrendl_fd_check(char *s, int fd);
int		ft_putstr_fd_check(char *s, int fd);

#endif
