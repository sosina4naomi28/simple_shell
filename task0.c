#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 100
/**
 *prompt - the function  implements built-inshandle special characters : ", ', `, \, *, &, #
 * be able to move the cursorhandle commands with arguments
 * Return: 0 success
 */
void prompt() {
    printf("$ ");
    fflush(stdout);
}

void execute_command(char* command) {
    pid_t pid = fork();

    if (pid < 0) {
        // Fork failed
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        // Child process
        if (execlp(command, command, NULL) == -1) {
            perror("Command not found");
            exit(1);
        }
    } else {
        // Parent process
        waitpid(pid, NULL, 0);
    }
}

int main() {
    char command[MAX_COMMAND_LENGTH];

    while (1) {
        prompt();

        if (fgets(command, sizeof(command), stdin) == NULL)
            break;

        command[strcspn(command, "\n")] = '\0'; // Remove trailing newline

        execute_command(command);
    }

    return 0;
}
