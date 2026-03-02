#include <stdio.h> /* Standard input-output library for printf and fgets */
#include <ctype.h> /* Library for character handling functions like isspace */
#include <string.h> /* Library for string manipulation functions like strlen */
#include "Shani_Peled_remove_blanks.h" /* Local header file for function prototypes */

#define DEBUG_SHANI /* Macro to enable or disable debug print messages */
#define STRING_MAX_LENGTH 100 /* Constant defining the maximum buffer size for input */

void remove_blanks(char *str) { /* Function to remove all whitespace from a string in-place */
    char *read_ptr = str; /* Pointer used to traverse and read each character */
    char *write_ptr = str; /* Pointer used to track where to write non-space characters */

    #ifdef DEBUG_SHANI /* Conditional check to see if debug mode is active */
    printf("\n******** Shani Peled DEBUG_SHANI msg **************\n"); /* Debug header */
    printf("Entering remove_blanks function\n"); /* Trace message for function entry */
    #endif /* End of conditional debug section */

    if (str == NULL) return; /* Safety check to prevent processing a null pointer */

    while (*read_ptr != '\0') { /* Iterate until the end of the string is reached */
        if (!isspace((unsigned char)*read_ptr)) { /* Check if current character is not a space */
            #ifdef DEBUG_SHANI /* Debug info for kept characters */
            printf("Keeping char: '%c'\n", *read_ptr); /* Print character being preserved */
            #endif /* End of debug section */
            *write_ptr = *read_ptr; /* Move the valid character to the write position */
            write_ptr++; /* Advance write pointer to the next available slot */
        } else { /* Executed if the character is a whitespace */
            #ifdef DEBUG_SHANI /* Debug info for removed spaces */
            printf("Removing blank space\n"); /* Trace message for space removal */
            #endif /* End of debug section */
        } /* End of if-else block */
        read_ptr++; /* Always advance the read pointer to the next character */
    } /* End of while loop */
    *write_ptr = '\0'; /* Terminate the modified string with a null character */

    #ifdef DEBUG_SHANI /* Final debug message */
    printf("Function finished processing\n"); /* Trace message for function completion */
    printf("*********************************************\n\n"); /* Debug footer */
    #endif /* End of debug section */
} /* End of remove_blanks function */

int main() { /* Main entry point of the program */
    int c; /* Temporary variable for character clearing */
    char line[STRING_MAX_LENGTH]; /* Array to store user input based on max length */
    
    printf("Please enter a string (Max %d chars, EOF to finish):\n", STRING_MAX_LENGTH - 1); /* User prompt */

    while (fgets(line, sizeof(line), stdin)) { /* Read input line by line until EOF */
        size_t len = strlen(line); /* Calculate the length of the string received */

        /* Validate if the string is too long (buffer full and no newline found) */
        if (len >= STRING_MAX_LENGTH - 1 && line[len-1] != '\n') { /* Condition for overflow */
            printf("\n!!! ERROR: String too long. Max is %d. !!!\n", STRING_MAX_LENGTH - 2); /* Error msg */
            while ((c = getchar()) != '\n' && c != EOF); /* Clear remaining chars from input buffer */
            printf("Please re-enter a legal string:\n"); /* Request new input */
            continue; /* Skip processing and restart loop */
        } /* End of length overflow check */

        /* Validate if the string is too short (only a newline character) */
        if (len <= 1 && line[0] == '\n') { /* Condition for empty input */
            printf("\n!!! ERROR: String is too short. !!!\n"); /* Error message for empty line */
            printf("Please re-enter a legal string:\n"); /* Request new input */
            continue; /* Skip processing and restart loop */
        } /* End of short string check */

        printf("The Input string:\n\"%s\"", line); /* Display the original string with quotes */
        remove_blanks(line); /* Call the function to strip whitespaces */
        printf("The string at the end of the function:\n\"%s\"\n", line); /* Display result */
        printf("\nPlease enter next string (or Ctrl+Z):\n"); /* Prompt for next iteration */
    } /* End of while loop */

    return 0; /* Exit program successfully */
} /* End of main function */