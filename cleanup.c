#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>


int clean_name(char *str, char *old_path);


int main(int argc, char *argv[]) {

    if (argc != 2) {
        fprintf(stderr, "usage error. missing <path> argument\nusage: <path>\n");
        return EXIT_FAILURE;
    }

    DIR *dir_ptr;
    struct dirent *dir;
    dir_ptr = opendir(argv[1]);

    if (dir_ptr == NULL) {
        perror("error opening dir");
        return EXIT_FAILURE;
    }

    while ((dir = readdir(dir_ptr)) != NULL) {
        if (dir->d_type == DT_DIR) {
            continue;
        }
        clean_name(dir->d_name, argv[1]);
    }

    return EXIT_FAILURE;
}


int clean_name(char *str, char *old_path) {
    char temp_buffer[256];
    char *str_ptr;
    char *path_ptr;
    int index = 0;

    str_ptr = str;
    while (*str_ptr) {
        if (isspace(*str_ptr)) {
            temp_buffer[index++] = '_';
            str_ptr++;
            while (isspace(*str_ptr)) {
                str_ptr++;
            }
        } else {
            temp_buffer[index++] = *str_ptr++;
        }
    }

    path_ptr = malloc(strlen(old_path) + strlen(temp_buffer) + 1);
    if (path_ptr == NULL) {
        fprintf(stderr, "Error allocating memory.\n");
        perror(NULL);
        return EXIT_FAILURE;
    }

    strncpy(path_ptr, old_path, strlen(old_path) + 1);
    strcat(path_ptr, temp_buffer);
    printf("new path: %s\n", path_ptr);
    free(path_ptr);

    return EXIT_SUCCESS;
}
