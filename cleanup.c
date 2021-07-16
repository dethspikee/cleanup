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
    int index = 0;
    char temp_buffer[256];
    char *str_ptr;
    char *real_path;

    if ((real_path = realpath(old_path, NULL)) == NULL) {
        perror("real path error");
        return EXIT_FAILURE;
    }

    str_ptr = str;
    temp_buffer[index++] = '/';
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
    temp_buffer[index] = '\0';

    char *new_path = malloc(sizeof(temp_buffer) + sizeof(real_path));
    strncpy(new_path, real_path, strlen(real_path) + 1);
    strcat(new_path, temp_buffer);
    printf("path: %s\n", new_path);
    free(new_path);

    return EXIT_SUCCESS;
}
