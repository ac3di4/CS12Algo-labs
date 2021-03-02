#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *readLine();
char *filterLine(char *);

int main() {
    char *line = readLine(), *res;
    while (line != NULL) {
        printf("source: '%s'\n", line);
        res = filterLine(line);
        printf("result: '%s'\n", res);
        free(res);
        free(line);
        line = readLine();
    }

    return 0;
}

/// return NULL if read failed
char *readLine() {
    char buf[1024]; // reading to a static buffer
    int n;
    do {
        n = scanf("%1023[^\n]", buf);
        if (n == 0)
            scanf("%*\n");
    } while (n == 0);
    if (n <= 0)
        return NULL; // nothing read   
    // malloc char pointer and copy buf to it 
    n = strlen(buf);
    char *res = malloc((n + 1) * sizeof(char));
    strcpy(res, buf);
    return res;
}

/// filter line (src gets destroyed)
char *filterLine(char *line) {
    int n = strlen(line);
    char *new_line = malloc((n + 1) * sizeof(char));
    *new_line = '\0';
    char *word = strtok(line, " \t");
    while (word != NULL) {
        if (word[0] == word[strlen(word) - 1]) { // last character equals first
            strcat(new_line, word); // and then word
            strcat(new_line, " "); // add space
        }
        word = strtok(NULL, " \t");
    }
    n = strlen(new_line);
    new_line[n - 1] = '\0'; // remove last space
    new_line = realloc(new_line, n * sizeof(char));
    return new_line;
}