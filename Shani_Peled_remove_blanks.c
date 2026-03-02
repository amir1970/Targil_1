#include <stdio.h>
#include <ctype.h>
#include "Shani_Peled_remove_blanks.h"

void remove_blanks(char *str) {
    char *read_ptr = str;
    char *write_ptr = str;

    if (str == NULL) return;

    while (*read_ptr != '\0') {
        /* isspace checks for ' ', '\t', '\n', etc. */
        if (!isspace((unsigned char)*read_ptr)) {
            *write_ptr = *read_ptr;
            write_ptr++;
        }
        read_ptr++;
    }
    /* Terminate the string at the new length */
    *write_ptr = '\0';
}

int main() {
    char line[1000]; /* הגדרת אורך מקסימלי סביר כפי שצוין בהערות */

    printf("Please enter a string (EOF to finish):\n");

    while (fgets(line, sizeof(line), stdin)) {
        printf("\nThe Input string:\n\"%s\"", line);
        printf("The string as received by the function:\n\"%s\"", line);
        
        remove_blanks(line);
        
        printf("The string at the end of the function:\n\"%s\"\n", line);
        printf("\nPlease enter next string (or Ctrl+D):\n");
    }

    return 0;
}