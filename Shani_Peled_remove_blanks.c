#include <stdio.h> /* Standard input-output library for printf and fgets */
#include <ctype.h> /* Library for character handling functions like isspace */
#include <string.h> /* Library for string manipulation functions like strlen */
#include "Shani_Peled_remove_blanks.h" /* Local header file for function prototypes */

/* #define DEBUG_SHANI  Macro to enable or disable debug print messages */
#define STRING_MAX_LENGTH 100 /* Constant defining the maximum buffer size for input */


void remove_blanks(char *str) { /* Function to remove spaces, tabs, and newlines from a string in-place */
    char *read_ptr = str; /* Pointer used to traverse and read each character from the original string */
    char *write_ptr = str; /* Pointer used to track the position to write the next valid character */

    #ifdef DEBUG_SHANI /* Conditional preprocessor directive to check if debug mode is active */
    printf("\n******** Shani Peled DEBUG_SHANI msg **************\n"); /* Print a visual separator for debug output */
    printf("Entering remove_blanks function\n"); /* Print a trace message indicating the start of the function */
    #endif /* End of the conditional debug section */

    if (str == NULL) return; /* Safety check: exit the function immediately if a null pointer is passed */

    /* Mandatory assignment requirement: Print the string BEFORE modifications */
    printf("The original string is:\n\"%s\"\n", str); /* Display the unmodified string surrounded by quotes */

    while (*read_ptr != '\0') { /* Loop through the string until the null terminator is encountered */
        
        /* Check if the current character is NOT a space, NOT a tab, and NOT a newline */
        if (*read_ptr != ' ' && *read_ptr != '\t' && *read_ptr != '\n') { 
            #ifdef DEBUG_SHANI /* Check if debug mode is enabled for character preservation */
            printf("Keeping char: '%c'\n", *read_ptr); /* Debug print showing which character is being kept */
            #endif /* End of debug section */
            
            *write_ptr = *read_ptr; /* Copy the valid character to the current write position */
            write_ptr++; /* Advance the write pointer to the next available slot */
        } else { /* Executed if the character IS a space, tab, or newline */
            #ifdef DEBUG_SHANI /* Check if debug mode is enabled for character removal */
            printf("Removing blank space\n"); /* Debug print indicating a whitespace character is being skipped */
            #endif /* End of debug section */
        } /* End of the if-else block */
        
        read_ptr++; /* Always advance the read pointer to evaluate the next character in the string */
    } /* End of the while loop */
    
    *write_ptr = '\0'; /* Add a null terminator at the final write position to properly close the new string */

    /* Mandatory assignment requirement: Print the string AFTER modifications */
    printf("The string at the end of the function:\n\"%s\"\n", str); /* Display the cleaned string surrounded by quotes */

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

        /* Called function handles all required printing (Before & After) */
        remove_blanks(line); 
        
        printf("\nPlease enter next string (or Ctrl+Z):\n"); /* Prompt for next iteration */
    } /* End of while loop */

    return 0; /* Exit program successfully */
} /* End of main function */