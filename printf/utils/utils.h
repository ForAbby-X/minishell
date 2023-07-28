/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 10:49:32 by olimarti          #+#    #+#             */
/*   Updated: 2022/12/20 13:36:49 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stddef.h>
# include <unistd.h>

int	ft_putnbr_base(long n, long base, const char *base_alphabet);
int	ft_put_u_nbr_base(unsigned long n, unsigned long base,
		const char *base_alphabet);

int	ft_putchar(const char c);
int	ft_putstr(char *s);

#endif
