/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 00:36:30 by olimarti          #+#    #+#             */
/*   Updated: 2023/07/04 12:19:01 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "vector.h"
# include "error.h"
# include "env.h"
# include "token.h"

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>

# include <sys/wait.h>

typedef struct s_exec_command
{
	t_vector	args;
	t_vector	redirs;
}	t_exec_command;

char		*join_path(char *dir, char *prog_name);
char		**parse_paths(char *path_str);

char		*get_command_path(char *file, t_vector *const env);
int			ft_execvpe(char *file, t_vector const *argv, t_vector *const env);

t_merror	exec_command_init(t_exec_command *const command);
void		exec_command_display(void *const object);
void		*exec_command_cpy(void *dest, void *src, t_length const len);
void		exec_command_destroy(void *const object);
void		exec_command_clear(void *const object);

void		arg_display(void *const object);
void		arg_destroy(void *const object);

t_merror	run_command(t_exec_command *command, t_vector *env);
t_merror	handle_redirs(t_vector *redirs);
t_merror	restore_redirs(int saved_stdin, int saved_stdout);

t_merror	spawn_command(t_exec_command *command, t_vector *env,
				int in_fd, int out_fd);
t_merror	exec_piped_commands(t_exec_command *commands,
				t_length commands_count, t_vector *env);
t_merror	exec_commands(t_vector *commands, t_vector *env);

t_merror	exec_builtins_layer(t_exec_command *commands,
				t_length commands_count, t_vector *env);

#endif
