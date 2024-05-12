// #include <stdio.h>
// #include <libc.h>
// int is_single(char *str)
// {
// 	int s;
// 	int d;
// 	int i;

// 	i = 0;
// 	s = d = 0;
// 	int j = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '\'' && d == 0)
// 			s = s + 1;
// 		else if (str[i] == '"' && s == 0)
// 			d = d + 1;
// 		if (d == 2)
// 			d = 0;
// 		if (s == 2)
// 			s = 0;
// 		if (str[i] == '$')
// 			break;
// 		i++;
// 	}
// 	if (s == 1)
// 		return (1);
// 	else
// 		return (0);

// 	return (0);
// }
// void f()
// {
// 	system("leaks a.out");
// }
// int main()
// {
// 	atexit(f);
// 	// char *str = "  \"'\"'$PWD'\"'\"   ";
// 	char *str = "  'PWD'   ";
// 	printf("%d\n", is_single(str));
	
// 	return (0);
// }

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TOKEN_LENGTH 100

char** split_with_quotes(const char* text) {
    char** tokens = malloc(sizeof(char*) * MAX_TOKEN_LENGTH);
    int token_count = 0;
    int in_quote = 0;
    const char* start = text;
    const char* end = text;

    while (*end != '\0') {
        if (*end == '"' || *end == '\'') {
            in_quote = !in_quote;
            end++;
        } else if ((*end == ' ' || *end == '\t') && !in_quote) {
            int length = end - start;
            if (length > 0) {
                tokens[token_count] = malloc(sizeof(char) * (length + 1));
                strncpy(tokens[token_count], start, length);
                tokens[token_count][length] = '\0';
                token_count++;
            }
            while (*end == ' ' || *end == '\t') {
                end++;
            }
            start = end;
        } else {
            end++;
        }
    }

    int length = end - start;
    if (length > 0) {
        tokens[token_count] = malloc(sizeof(char) * (length + 1));
        strncpy(tokens[token_count], start, length);
        tokens[token_count][length] = '\0';
        token_count++;
    }

    tokens[token_count] = NULL;
    return tokens;
}

void free_tokens(char** tokens) {
    for (int i = 0; tokens[i] != NULL; i++) {
        free(tokens[i]);
    }
    free(tokens);
}

int main() {
    const char* text = "export x=\"ls -la\" \"    kk    ll\"  'll k'";
    char** tokens = split_with_quotes(text);
    
    printf("Tokens:\n");
    for (int i = 0; tokens[i] != NULL; i++) {
        printf("%s\n", tokens[i]);
    }
    
    free_tokens(tokens);

    return 0;
}
