#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>


void clean_name(char *str);


int main(void) {
    DIR *dir_ptr;
    struct dirent *dir;
    dir_ptr = opendir(".");
    int counter = 0;

    while ((dir = readdir(dir_ptr)) != NULL) {
        if (dir->d_type == DT_DIR) {
            continue;
        }
        clean_name(dir->d_name);
        counter++;
        if (counter == 2) {
            break;
        }
    }

    return EXIT_FAILURE;
}


void clean_name(char *str) {
    char temp_buffer[256];
    char *ptr = temp_buffer;
    strncpy(temp_buffer, str, strlen(str) + 1);
    while (*ptr) {
        printf("%c", *ptr++);
    }
    printf("\n");
}
