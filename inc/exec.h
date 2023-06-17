#ifndef EXEC_H
#define EXEC_H

# include "vector.h"
# include "env.h"

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>

char	*join_path(char *dir, char *prog_name);
char	**parse_paths(char *path_str);

char	*get_command_path(char *file, t_vector *const env);
int		ft_execvpe(char *file, t_vector  const *argv, t_vector *const env);

#endif