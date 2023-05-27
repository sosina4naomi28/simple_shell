#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 100

/**
 * prompt - the function  implements built-inshandle
 * Return: 0 success
 */
void prompt(void)
{
	printf("$ ");
	fflush(stdout);
}
/**
 * execute_command  - special characters : ", ', `, \, *, &, #
 * @command: NUL or lengthL
 * Return: nothing
 */
void execute_command(char *command)
{
	pid_t pid = fork();

	if (pid < 0)
	{
		exit(1);
	}
	else if (pid == 0)
	{
		if (execlp(command, command, NULL) == -1)
		{
			perror("Command not found");
			exit(1);
		}
	}
	else
	{
		waitpid(pid, NULL, 0);
	}
}
/**
 * main - function that move the cursorhandle commands with arguments
 * Return: 0 success
 */
int main(void)
{
	char command[MAX_COMMAND_LENGTH];

	while (1)
	{
		prompt();
		if (fgets(command, sizeof(command), stdin) == NULL)
			break;
		command[strcspn(command, "\n")] = '\0';
		execute_command(command);
	}
	return (0);
}
