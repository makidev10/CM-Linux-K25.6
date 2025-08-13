//LESSON 2
 
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <time.h>  
 
int main(int argc, char* argv[]) {
    if (argc <= 1) {
        printf("Usage: ./filestat <file_path>\n");
        return 1;
    }
 
    const char *filepath = argv[1];
    struct stat st;
 
    if (stat(filepath, &st) == 0) {
        //Print file path
        char resolved_path[PATH_MAX];
        if (realpath(filepath, resolved_path) != NULL) {
            printf("File path: %s.\n", resolved_path);
        } else {
            printf("Can not get resolved path of file: %s", filepath);
            return 1;
        }
   
        //Print file type
        if (S_ISREG(st.st_mode)) {
            printf("File type: Regular file.\n");
        } else if (S_ISDIR(st.st_mode)) {
            printf("File type: Directory.\n");
        } else {
            printf("File type: Symbolic Link.\n");
        }
 
        //Print file size
        printf("File size: %d bytes\n", (int)st.st_size);
 
        //Print last modified time
        time_t last_modified_time = st.st_mtime;
        char buffer[80];
        struct tm *time_struct = gmtime(&last_modified_time);
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", time_struct);
        printf("Last modified: %s.\n", buffer);
    } else {
        printf("Path '%s' does not exist or is inaccessible.\n", filepath);
        return 1;
    }
 
    return 0;
}