#ifndef ENV_H
# define ENV_H

char	**env_add(t_vector *const vector, char	*const obj)
		__attribute__((always_inline));

char	**env_get(t_vector *const vector, t_length const index)
		__attribute__((always_inline));

char	*ft_getenv(t_vector *const vector, const char *name);

#endif
