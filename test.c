#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

typedef struct noeud_cmd {
    int in;
    int out;
    char *redirection;
    char *cmd;
    struct noeud_cmd *next;
} noeud_cmd;

void execute_command(noeud_cmd *node) {
    int fd_in = dup(STDIN_FILENO); // Sauvegarde de l'entrée standard
    int fd_out = dup(STDOUT_FILENO); // Sauvegarde de la sortie standard

    // Redirection de l'entrée et de la sortie
    if (node->in != STDIN_FILENO) {
        dup2(node->in, STDIN_FILENO);
        close(node->in);
    }
    if (node->out != STDOUT_FILENO) {
        dup2(node->out, STDOUT_FILENO);
        close(node->out);
    }

    // Exécution de la commande avec gestion de la redirection de sortie
    if (node->cmd != NULL) {
        if (node->redirection != NULL) {
            int fd = open(node->redirection, O_WRONLY | O_CREAT | O_TRUNC, 0666);
            if (fd == -1) {
                perror("open");
                exit(EXIT_FAILURE);
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        char *args[] = {node->cmd, NULL};
        execvp(node->cmd, args);
        // En cas d'échec de execvp
        perror("execvp");
        exit(EXIT_FAILURE);
    }

    // Restauration des descripteurs de fichiers standard
    dup2(fd_in, STDIN_FILENO);
    dup2(fd_out, STDOUT_FILENO);
    close(fd_in);
    close(fd_out);
}

void execute_pipeline(noeud_cmd *head) {
    int pipefd[2];
    pid_t pid;

    noeud_cmd *current = head;
    int fd_in = STDIN_FILENO;

    while (current != NULL) {
        // Création d'un pipe pour connecter l'entrée de la commande courante
        // à la sortie de la commande précédente (sauf pour la première commande)
        if (current->next != NULL) {
            if (pipe(pipefd) == -1) {
                perror("pipe");
                exit(EXIT_FAILURE);
            }
        }

        pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) { // Processus fils
            close(pipefd[0]); // Ferme le descripteur de fichier inutilisé dans le fils

            // Redirection de l'entrée
            current->in = fd_in;

            // Redirection de la sortie (sauf pour la dernière commande)
            if (current->next != NULL) {
                current->out = pipefd[1];
            }

            // Exécution de la commande
            execute_command(current);

            // Si nous sommes ici, il y a eu une erreur
            exit(EXIT_FAILURE);
        } else { // Processus parent
            close(pipefd[1]); // Ferme le descripteur de fichier inutilisé dans le parent
            close(fd_in); // Ferme l'entrée utilisée par le processus précédent

            // Déplacer le descripteur de fichier de lecture du pipe
            // pour qu'il soit utilisé comme entrée par le prochain processus
            fd_in = pipefd[0];

            current = current->next;
        }
    }

    // Attendre la fin de l'exécution de tous les processus fils
    while (wait(NULL) != -1);
}

int main() {
    // Code de test
    noeud_cmd *node1 = malloc(sizeof(noeud_cmd));
    node1->cmd = "ls";
    node1->redirection = NULL;
    node1->next = NULL;
    node1->next = malloc(sizeof(noeud_cmd));
    noeud_cmd *node2 = node1->next;
    node2->cmd = "cat";
    node2->redirection = NULL;
    node2->next = NULL;

    execute_pipeline(node1);

    free(node1);
    return 0;
}
