/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:40:35 by alde-fre          #+#    #+#             */
/*   Updated: 2023/06/22 00:32:16 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef ERROR_H
# define ERROR_H

# include <string.h>

typedef enum e_merror {
	SUCCESS,
	FAILURE,
	MEMORY_ERROR,
	PARSING_ERROR,
	CHILD_ERROR,
}	t_merror;

#endif
