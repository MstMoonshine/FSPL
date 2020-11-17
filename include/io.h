#ifndef IO_H
#define IO_H

int check_file_path_legal(int argc, char **argv);
char *output_filename(char *file_path); //generating output name using argv[1]

#endif