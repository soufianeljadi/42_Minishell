#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *value;
} Token;

Token* create_token(char *value) {
    Token *token = malloc(sizeof(Token));
    if (token == NULL) {
        fprintf(stderr, "Erreur lors de l'allocation de mémoire pour le jeton\n");
        exit(EXIT_FAILURE);
    }
    token->value = strdup(value);
    return token;
}

void free_token(Token *token) {
    free(token->value);
    free(token);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *ft_strtok(char *str, const char *delim)
{
    static char *last_str = NULL;  // Pointeur vers le dernier caractère non-délimitateur de la chaîne
    char *token_start;             // Pointeur vers le début du jeton
    const char *delim_ptr;         // Pointeur utilisé pour parcourir les délimiteurs

    // Si str est NULL, on utilise la valeur stockée dans last_str
    if (str == NULL)
        str = last_str;

    // Ignorer les délimiteurs au début de la chaîne
    while (*str && strchr(delim, *str))
        str++;

    // Si on a atteint la fin de la chaîne ou si la chaîne est vide, retourner NULL
    if (*str == '\0')
        return NULL;

    // Chercher le début du jeton
    token_start = str;

    // Trouver la fin du jeton
    while (*str && !strchr(delim, *str))
        str++;

    // Si on n'est pas arrivé à la fin de la chaîne, remplacer le délimiteur par un caractère nul
    if (*str != '\0')
        *str++ = '\0';

    // Mettre à jour last_str pour qu'il pointe vers le caractère suivant le dernier caractère non-délimitateur de la chaîne
    last_str = str;

    return token_start;
}

int main() {
    char str[] = "Ceci est, un exemple;de chaine.de caracteres";
    char delim[] = " ,;.";
    char *token;

    // Utiliser ft_strtok pour obtenir les jetons
    token = ft_strtok(str, delim);
    while (token != NULL) {
        printf("%s\n", token);
        token = ft_strtok(NULL, delim);
    }

    return 0;
}

Token** parse_command(char *command)
{
    Token **tokens = malloc(sizeof(Token*) * strlen(command));
    if (tokens == NULL)
    {
        fprintf(stderr, "Erreur lors de l'allocation de mémoire pour les jetons\n");
        exit(EXIT_FAILURE);
    }

    char *token_str = ft_strtok(command, " ");
    int token_count = 0;

    while (token_str != NULL)
    {
        tokens[token_count++] = create_token(token_str);
        token_str = ft_strtok(NULL, " ");
    }
    tokens[token_count] = NULL;

    return tokens;
}

void print_tokens(Token **tokens)
{
    for (int i = 0; tokens[i] != NULL; i++)
    {
        printf("%s\n", tokens[i]->value);
    }
}

// Fonction pour libérer la mémoire allouée aux jetons
void free_tokens(Token **tokens)
{
    for (int i = 0; tokens[i] != NULL; i++)
    {
        free_token(tokens[i]);
    }
    free(tokens);
}

int main()
{
    char command[] = "> cat < input.txt >> output.txt";
    Token **tokens = parse_command(command);

    printf("Jetons de la commande :\n");
    print_tokens(tokens);

    free_tokens(tokens);

    return 0;
}
