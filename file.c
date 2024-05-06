#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* modifierChaine(char* chaine) {
    char* nouvelleChaine = malloc(strlen(chaine) + 1);
    if (nouvelleChaine == NULL) {
        printf("Erreur d'allocation de mémoire.\n");
        exit(EXIT_FAILURE);
    }

    int i, j;
    int aTrouveEspace = 0;

    for (i = 0, j = 0; chaine[i] != '\0'; i++) {
        if (chaine[i] == '>') {
            if (chaine[i+1] == ' ') {
                nouvelleChaine[j++] = chaine[i++];
                nouvelleChaine[j++] = chaine[i];
                aTrouveEspace = 1;
                continue;
            }
        }

        if (aTrouveEspace) {
            if (chaine[i] == ' ') {
                continue;
            }
            aTrouveEspace = 0;
        }

        nouvelleChaine[j++] = chaine[i];
    }

    nouvelleChaine[j] = '\0';
    return nouvelleChaine;
}

int main() {
    char chaine[] = "<a <g hsjdhjs  > f1>";
    char* nouvelleChaine = modifierChaine(chaine);
    printf("Chaine modifiée: %s\n", nouvelleChaine);
    free(nouvelleChaine);
    return 0;
}
