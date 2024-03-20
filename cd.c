#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char new_path[1024];

    if (argc != 2) {
        fprintf(stderr, "Usage: %s directory\n", argv[0]);
        return 1;
    }

    // Check if the provided path is absolute
    if (argv[1][0] == '/') {
        strcpy(new_path, argv[1]); // If absolute, use as is
    } else {
        // If relative, concatenate with current working directory
        if (getcwd(new_path, sizeof(new_path)) == NULL) {
            perror("getcwd");
            return 1;
        }
        strcat(new_path, "/");
        strcat(new_path, argv[1]);
    }

    // Change the working directory
    if (chdir(new_path) != 0) {
        perror("chdir");
        return 1;
    }

    // Print the new working directory
    if (getcwd(new_path, sizeof(new_path)) != NULL) {
        printf("Current working directory: %s\n", new_path);
    } else {
        perror("getcwd");
        return 1;
    }

    return 0;
}
