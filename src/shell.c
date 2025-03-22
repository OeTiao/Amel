#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#define MAX_FILE_SIZE 1024 * 1024

int main(int argc, const char** argv) {
    if (argc <= 1) {

        FILE* mainf = fopen("examples/test.aml", "r");
        if (!mainf) {
            fprintf(stderr, "test.lsub was not found.\n");
            return 1;
        }

        
        char *main_source_code = malloc(MAX_FILE_SIZE);
        if (main_source_code == NULL) {
            fprintf(stderr, "Memory allocation for the source code failed.\n");
            fclose(mainf);
            return 1;
        }

        
        size_t bytes_read = fread(main_source_code, 1, MAX_FILE_SIZE - 1, mainf);
        if(bytes_read > MAX_FILE_SIZE) {
            main_source_code = realloc(main_source_code, bytes_read);
            if(main_source_code == NULL) {
                perror("Unable to allocate more heap memory for the main file's source.");
                return 1;
            }
        }
        main_source_code[bytes_read] = '\0'; 
        
        fclose(mainf);

       
        printf("%s\n", main_source_code);
        token *tokens;
        size_t tokens_len = tokenize(main_source_code, &tokens);
       
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