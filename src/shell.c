#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"

int main(int argc, const char** argv) {
    if (argc <= 1) {

        FILE* mainf = fopen("examples/test.aml", "r");
        if (!mainf) {
            fprintf(stderr, "test.lsub was not found.\n");
            return 1;
        }

        

        fseek(mainf, 0, SEEK_END);
        long file_size = ftell(mainf);
        fseek(mainf, 0, SEEK_SET); 

        
        char *main_source_code = malloc(file_size + 1);
        if (main_source_code == NULL) {
            fprintf(stderr, "Memory allocation for the source code failed.\n");
            fclose(mainf);
            return 1;
        }

        size_t bytes_read = fread(main_source_code, 1, file_size, mainf);
        main_source_code[bytes_read] = '\0';

        fclose(mainf);

       

        size_t tokens_len = 0;
        token *tokens = tokenize(main_source_code, &tokens_len);
        for(size_t i = 0; i < tokens_len; i++) {
            //printf("oi %zu", i);
            printf("\nValue: %s \tType: %d\n", tokens[i].value, tokens[i].type);
        }
        for(size_t i = 0; i < tokens_len; i++) {
            if(tokens[i].type == IDENTIFIER || tokens[i].type == NUMBER) {
                free(tokens[i].value);
            }
        }
        free(tokens);
        free(main_source_code);
    }
    else if (argc > 2) {
        printf("Too many arguments. Usage: lsub [file.lsub]\n");
    }
    else {
        //repl
    }

    return 0;
}