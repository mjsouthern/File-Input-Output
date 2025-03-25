/* 
Error Handling
Use perror() and exit() for user-friendly error handling.
*/

#include <stdio.h>
#include <stdlib.h>  // Required for exit() and EXIT_FAILURE

int main() {
    FILE *file = fopen("missing.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }    
    
    // If file opens, you can add reading logic here
    fclose(file);  // Always close files you open

    return 0;
}
