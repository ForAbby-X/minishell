#include "exec.h"

void	exec_command_display(void *const object)
{
	t_exec_command *const	command = object;

	printf("--Command--\nargs: ");
	vector_for_each(&command->args, &arg_display); //TODO use custom function
	printf("\nredirs : ");
	printf("REDIRS COUNT : %i\n", command->redirs.size);
	vector_for_each(&command->redirs, &token_display);
	printf("\n");

}

t_merror	exec_command_init(t_exec_command *const command)
{
	command->args = vector_create(sizeof(char *));
	if (command->args.buffer == NULL)
		return (MEMORY_ERROR);
	command->redirs = vector_create(sizeof(t_token));
	if (command->redirs.buffer == NULL)
		return (vector_destroy(&command->args), MEMORY_ERROR);
	return (SUCCESS);
}

void	*exec_command_cpy(void *dest, void *src, t_length const len)
{
	t_exec_command *const	dest1 = dest;
	t_exec_command *const	src1 = src;

	(void)len;
	*dest1 = *src1;
	exec_command_init(dest1);
	return (dest1);
}

void	exec_command_destroy(void *const object)
{
	t_exec_command *const	command = object;

	vector_for_each(&command->args, &arg_destroy);
	vector_destroy(&command->args);
	vector_for_each(&command->redirs, &token_display);
	vector_destroy(&command->redirs);
}

void	exec_command_clear(void *const object)
{
	t_exec_command *const	command = object;

	vector_for_each(&command->args, &arg_destroy);
	vector_clear(&command->args);
	vector_for_each(&command->redirs, &token_display);
	vector_clear(&command->redirs);
}