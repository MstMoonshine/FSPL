#include "include/io.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int check_file_path_legal(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file_path>\n", argv[0]);
        exit(1);
    } else if (argc > 2) {
        fprintf(stderr, "Too many arguments.\n");
        exit(1);
    }
    
    char *file_path = argv[1];
    if (strlen(file_path) <= 3 || strcmp(file_path + strlen(file_path) - 4, ".spl")) {
        fprintf(stderr, "Invalid file: .spl file expected\n");
        exit(1);
    } else if (!fopen(file_path, "r")) {
        perror(argv[1]);
        exit(1);
    }
    return 1;
}

char *output_filename(char *file_path) {
    char *output_name = malloc((strlen(file_path) + 1) * sizeof(char));
    for (int i = 0; i < strlen(file_path) - 3; i++)
        output_name[i] = file_path[i];
    output_name[strlen(file_path) - 3] = '\0';
    strcat(output_name, "out");
    return output_name;
}