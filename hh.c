#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct noued_cmd {
    char *cmd;
    char *redirection;
    struct noued_cmd *next;
} noued_cmd;

char *ft_strjoin(const char *s1, const char *s2)
{
    size_t len_s1 = 0;
    size_t len_s2 = 0;
    size_t i = 0;
    size_t j = 0;
    char *result;

    if (s1)
        while (s1[len_s1])
            len_s1++;
    if (s2)
        while (s2[len_s2])
            len_s2++;

    result = (char *)malloc(sizeof(char) * (len_s1 + len_s2 + 1));
    if (!result)
        return NULL;

    while (i < len_s1)
    {
        result[i] = s1[i];
        i++;
    }
    while (j < len_s2)
    {
        result[i + j] = s2[j];
        j++;
    }
    result[i + j] = '\0';

    return result;
}

noued_cmd *new_noued_cmd(char *commande, char *redirection)
{
    noued_cmd *nouveau_noeud = (noued_cmd *)malloc(sizeof(noued_cmd));
    if (!nouveau_noeud)
    {
        printf("Erreur d'allocation de mémoire\n");
        exit(EXIT_FAILURE);
    }
    if (!commande)
        nouveau_noeud->cmd = NULL;
    else
        nouveau_noeud->cmd = strdup(commande);
    nouveau_noeud->redirection = (redirection) ? strdup(redirection) : NULL;
    nouveau_noeud->next = NULL;
    return nouveau_noeud;
}

void add_back_noued_cmd(noued_cmd **tete, char *commande, char *redirection)
{
    if (!*tete)
        *tete = new_noued_cmd(commande, redirection);
    else if (!commande)
    {
        noued_cmd *courant = *tete;
        while (courant->next)
            courant = courant->next;
        courant->next = new_noued_cmd(commande, redirection);
    }
    else
    {
        noued_cmd *courant = *tete;
        while (courant->next)
            courant = courant->next;
        courant->next = new_noued_cmd(commande, redirection);
    }
}

void free_noued_cmd(noued_cmd *node)
{
    if (node == NULL)
        return;
    free_noued_cmd(node->next); // Free the next node recursively
    free(node->cmd); // Free the command string
    free(node->redirection); // Free the redirection string
    free(node); // Free the node itself
}

noued_cmd *split_args_by_pipe(char **args)
{
    noued_cmd *cmd = NULL;
    char *s = NULL;
    char *redirection = NULL;
    int i = 0;
    char *op_and_filename;
    char *tmp;
    
    while (args[i])
    {
        if (strcmp(args[i], "|") == 0) 
        {
            add_back_noued_cmd(&cmd, s, redirection);
            free(s);
            s = NULL;
            redirection = NULL;
        }
        else if (strcmp(args[i], "<") == 0 || strcmp(args[i], ">") == 0 || strcmp(args[i], ">>") == 0)
        {
            if (i == 0)
            {
                redirection = strdup(args[i]);
                i++;
            }
            else
            {
                tmp = strdup(args[i]);
                int j = i + 1;
                while (args[j] && (strcmp(args[j], "|") != 0))
                {
                    // Concaténer les noms de fichiers pour les redirections multiples
                    op_and_filename = ft_strjoin(tmp, args[j]);
                    free(tmp);
                    tmp = op_and_filename;
                    j++;
                }
                redirection = tmp;
                i = j - 1;
            }
        }
        else
        {
            if (!s)
                s = strdup(args[i]);
            else
            {
                char *temp = ft_strjoin(s, " ");
                free(s);
                s = ft_strjoin(temp, args[i]);
                free(temp);
            }
        }
        i++;
    }
    
    add_back_noued_cmd(&cmd, s, redirection);
    free(s);
    //redirection = NULL;
    
    return cmd;
}

int main() {
    char *args[] = {">", "jj", "|", ">", "salah", NULL};
    noued_cmd *result = split_args_by_pipe(args);
    noued_cmd *current = result;
    while (current) {
        printf("Commande: %s\n", current->cmd);
        printf("Redirection: %s\n", current->redirection ? current->redirection : "(pas de redirection)");
        printf("\n");
        current = current->next;
    }
    // Libérer la mémoire des nœuds de la liste chaînée
    free_noued_cmd(result);
    return 0;
}
