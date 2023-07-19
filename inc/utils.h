/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 02:26:36 by alde-fre          #+#    #+#             */
/*   Updated: 2023/07/19 18:23:33 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>

char	*ft_getpid(void);
int		ft_strcpyl(char *dst, char *src);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_atoi_validate(char *str, int *result);

#endif
