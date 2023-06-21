/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 21:48:41 by olivier           #+#    #+#             */
/*   Updated: 2023/06/22 01:01:11 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"


t_merror run_command(t_exec_command *command, t_vector *env)
{
	handle_redirs(&command->redirs);
	ft_execvpe(*(char **)vector_get(&(command->args), 0), &(command->args), env);
	return (FAILURE);
}

// t_merror spawn_command(t_exec_command *command, t_vector *env)
// {
// 	int cpid;

// 	cpid = fork();
// 	if (cpid == 0)
// 	{
// 		//PARENT
// 	}
// 	else
// 	{
// 		//child
// 	}
// }