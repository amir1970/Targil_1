#ifndef SHANI_PELED_REMOVE_BLANKS_H /* Directive to prevent multiple inclusions of this header file during compilation */
#define SHANI_PELED_REMOVE_BLANKS_H /* Define the macro to mark that this header has been processed */

/* * Function: Shani_Peled_remove_blanks
 * --------------------
 * Removes all white-space characters (space, tab, newline) from a string.
 * The modification is done in-place on the original string.
 *
 * str: The null-terminated string to be modified.
 */

void remove_blanks(char *str); /* Prototype for the function that strips whitespaces from the input string */

#endif /* End of the include guard to close the ifndef block */