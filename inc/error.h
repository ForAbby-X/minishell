/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:40:35 by alde-fre          #+#    #+#             */
/*   Updated: 2023/06/20 16:52:06 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

typedef enum e_merror {
	SUCCESS,
	FAILURE,
	MEMORY_ERROR,
	PARSING_ERROR
}	t_merror;

#endif
