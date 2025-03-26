/* 
Appending Data
*/

#include <stdio.h>

int main() {
    FILE *pWrite = fopen("hobbies.dat", "a");
    if (pWrite != NULL) {
        fprintf(pWrite, "SMCC Bigger, Better, Stronger, Holier\n");
        printf("Successfully appending a text in hobbies.dat file");
        fclose(pWrite);
    }    
    
    return 0;
}
