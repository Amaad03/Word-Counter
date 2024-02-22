#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <ctype.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char* argv[]) {
    int file = open(argv[1], O_RDONLY);

    if (file < 0) {
           printf("Error: %s\n", strerror(errno));
        
        return -1;
    }
    if (argc != 2) {
        printf("Error: Expected one argument, found %d\n", argc - 1);
        return -1;
    }
    
   
    int totLines = 0;
    int totWords = 0;
    int totChars = 0;
    int prevIsSpace = 1;
    char buffer[1];

    while (read(file, buffer, 1) > 0) {
        totChars++;
        if (isspace(buffer[0])) {
            prevIsSpace = 1;
           
            if (buffer[0] == '\n') {
                totLines++;
            }
        } else {
            if (prevIsSpace) {
                totWords++;
            }
            prevIsSpace = 0;
        }
    }

    if (prevIsSpace != 1) { 
        totLines++;
    }

    if (totChars == 1 && isspace(buffer[0]) && totWords == 0) {
        totLines++;

    }
     if (totChars == 0) {
        printf("Error: the file is empty\n");
        printf("%d %d %d %s\n", totLines, totWords, totChars, argv[1]);
        return -1;
    }


    int closed = close(file);
    if (closed == 1) {
        printf("Error: %s\n", strerror(errno));
        return -1;
    }

    printf("%d %d %d %s\n", totLines, totWords, totChars, argv[1]);
    return 0;
}
