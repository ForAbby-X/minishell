/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 01:00:33 by olimarti          #+#    #+#             */
/*   Updated: 2023/06/24 01:00:48 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	arg_display(void *const object)
{
	char const **const	arg = object;

	printf("[%s]", *arg);
}

void	arg_destroy(void *const object)
{
	char **const	arg = object;

	free(*arg);
}
