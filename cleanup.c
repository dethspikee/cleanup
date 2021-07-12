#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>


void clean_name(char *str);


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
        clean_name(dir->d_name);
    }

    return EXIT_FAILURE;
}


void clean_name(char *str) {
    char temp_buffer[256];
    char *ptr = str;
    int index = 0;
    while (*ptr) {
        if (isspace(*ptr)) {
            temp_buffer[index++] = '_';
            ptr++;
            while (isspace(*ptr)) {
                ptr++;
            }
        } else {
            temp_buffer[index++] = *ptr++;
        }
    }
    printf("%s\n", temp_buffer);
}
