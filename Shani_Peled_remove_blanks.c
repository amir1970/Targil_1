#include <stdio.h> /*Include library for handling standards input output*/
#include <ctype.h> /*Include library for hisspace(c):andling chars e.g. */
#include "Shani_Peled_remove_blanks.h"  /*Include Header file for this C file (Functions prototypes etc...)*/

#define DEBUG_SHANI /*Define the MACRO that control the Enable/Disable DEBUG_SHANI prints*/
#define STRING_MAX_LENGTH (unsigned int)100/*Define the MACRO that control the String Maximum Length, Casting to unsigned integer*/
/**
 * @function: remove_blanks
 * * @input: String Length Define by STRING_MAX_LENGTH Macro and the string itself that the user input, the function will handle it and remove all the blannks from it
 * - char *str: A pointer to a null-terminated string. 
 * * @output: 
 * - None (The function modifies the input string in-place).
 * * @processing: 
 * - The function uses two pointers (read and write) to iterate through the string.
 * - It identifies "white-space" characters (blanks, tabs, newlines) using the isspace() function.
 * - Non-blank characters are shifted to the write position, effectively overwriting blanks.
 * - A new null terminator '\0' is placed at the end of the modified sequence.
 * - Includes conditional DEBUG_SHANI logging if the DEBUG_SHANI macro is defined during compilation.
 */

void remove_blanks(char *str) {
    char *read_ptr = str; /*Pointer for read char from */
    char *write_ptr = str;/*Pointer for write for handling remove space in the user input string*/

    /*DEBUG_SHANI msg for indication that the program enter this function void remove_blanks(char *str)*/
    #ifdef DEBUG_SHANI
    printf("\n******** Shani Peled DEBUG_SHANI msg **************\n");
    printf("Entering remove_blanks function\n");
    #endif

    /*Check if the input string is NULL, if yes print the input string length is zero*/
    if (str == NULL) { 
        #ifdef DEBUG_SHANI
        printf("\n******** Shani Peled DEBUG_SHANI msg **************\n");
        printf("The input string length is Zero \n");
        #endif
              
        return;
        }

    /*While Loop to handle the user input string, exit condition is Enter (new line '\0)*/
    while (*read_ptr != '\0') {
        if (!isspace((unsigned char)*read_ptr)) {/*Check if the current input char in the string is space or not using isspace(x) function*/
            #ifdef DEBUG_SHANI
            printf("\n******** Shani Peled DEBUG_SHANI msg **************\n");
            printf("Keeping char: '%c'\n", *read_ptr);
            #endif

            *write_ptr = *read_ptr;/*Compare the read pointer value to write pointer value*/
            write_ptr++;/*Increase the write char ptr by one to point the next char in the string*/
        } else {
            #ifdef DEBUG_SHANI
            printf("\n******** Shani Peled DEBUG_SHANI msg **************\n");
            printf("Removing blank space\n");
            #endif
        }
        read_ptr++;
    }
    *write_ptr = '\0';

    #ifdef DEBUG_SHANI
    printf("Function finished processing\n");
    printf("*********************************************\n\n");
    #endif
}

int main() {
    char line[STRING_MAX_LENGTH];
    
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