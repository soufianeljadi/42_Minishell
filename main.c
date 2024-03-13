#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

#define MAX_COMMAND_LENGTH 100

int main(int arc, char **arv, char **env)
{
    int i = 0;

    while (env[i])
    {
        printf("%s\n", env[i]);
        i++;
    }
}


// int main() {
//     char *command;

//     while (1) {

//         command = readline("bash: ");
//         if (!command) {
//             // Error or EOF while reading input
//             break;
//         }
        
//         // Check for exit command
//         if (strcmp(command, "exit") == 0) {
//             printf("Exiting...\n");
//             free(command);
//             break;
//         }

//         // Execute the command
//         pid_t pid = fork();
//         if (pid == -1) {
//             perror("fork");
//         } else if (pid == 0) {  // Child process
//             execlp(command, command, NULL);
//             perror("exec");
//             exit(EXIT_FAILURE);
//         } else {  // Parent process
//             waitpid(pid, NULL, 0);
//         }

//         free(command);
//     }

//     return 0;
// }
