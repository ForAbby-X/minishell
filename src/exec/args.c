#include "exec.h"

void	arg_display(void *const object)
{
	char const **const arg = object;

	printf("[%s]", *arg);
}

void	arg_destroy(void *const object)
{
	char **const	arg = object;
	free(*arg);
}
