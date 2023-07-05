/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 18:10:19 by alde-fre          #+#    #+#             */
/*   Updated: 2023/06/28 18:16:57 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "word.h"

void	word_display(void *const object)
{
	char *const *const	word = object;

	printf("[\e[94m%s\e[0m] ", *word);
}

void	word_destroy(void *const object)
{
	char *const *const	word = object;

	free(*word);
}
