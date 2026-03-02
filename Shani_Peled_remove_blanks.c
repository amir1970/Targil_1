#include <stdio.h> //Include library for handling standards input output
#include <ctype.h> //Includei library for hisspace(c):andling chars e.g. 
#include "Shani_Peled_remove_blanks.h"  //Includei Header file for this C file (Functions prototypes etc...)

/**
 * @function: remove_blanks
 * * @input: 
 * - char *str: A pointer to a null-terminated string.
 * * @output: 
 * - None (The function modifies the input string in-place).
 * * @processing: 
 * - The function uses two pointers (read and write) to iterate through the string.
 * - It identifies "white-space" characters (blanks, tabs, newlines) using the isspace() function.
 * - Non-blank characters are shifted to the write position, effectively overwriting blanks.
 * - A new null terminator '\0' is placed at the end of the modified sequence.
 * - Includes conditional debug logging if the DEBUG macro is defined during compilation.
 */

void remove_blanks(char *str) {
    char *read_ptr = str; //Pointer for read char from user
    char *write_ptr = str;//Pointer for write for handling remove space in the user input string

    //Debug msg for indication that the program enter this function void remove_blanks(char *str)
    #ifdef DEBUG
    printf("\n******** Shani Peled Debug msg **************\n");
    printf("Entering remove_blanks function\n");
    #endif

    //Check if the input string is NULL, if yes print the input string length is zero
    if (str == NULL) { 
        #ifdef DEBUG
        printf("\n******** Shani Peled Debug msg **************\n");
        printf("The input string length is Zero \n");
        #endif
              
        return;
        }

    //While Loop to handle the user input string, exit condition is Enter (new line '\0)
    while (*read_ptr != '\0') {
        if (!isspace((unsigned char)*read_ptr)) {//Check if the current input char in the string is space or not using isspace(x) function
            #ifdef DEBUG
            printf("\n******** Shani Peled Debug msg **************\n");
            printf("Keeping char: '%c'\n", *read_ptr);
            #endif

            *write_ptr = *read_ptr;// Compare the read pointer value to write pointer value
            write_ptr++;//Increase the write char ptr by one to point the next char in the string
        } else {
            #ifdef DEBUG
            printf("\n******** Shani Peled Debug msg **************\n");
            printf("Removing blank space\n");
            #endif
        }
        read_ptr++;
    }
    *write_ptr = '\0';

    #ifdef DEBUG
    printf("Function finished processing\n");
    printf("*********************************************\n\n");
    #endif
}

int main() {
    char line[1000];
    
    printf("Please enter a string (EOF to finish):\n");

    while (fgets(line, sizeof(line), stdin)) {
        /* Print the desired  output format*/
        printf("The Input string:\n\"%s\"", line);
        printf("The string as received by the function:\n\"%s\"", line);
        
        remove_blanks(line);
        
        printf("The string at the end of the function:\n\"%s\"\n", line);
        printf("\nPlease enter next string (or Ctrl+Z):\n");
    }

    return 0;
}