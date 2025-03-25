/* 
Appending Data
*/

#include <stdio.h>

int main() {
    FILE *pWrite = fopen("hobbies.dat", "a");
    if (pWrite != NULL) {
        fprintf(pWrite, "Sam Guitar\n");
        fclose(pWrite);
    }    
    
    return 0;
}
