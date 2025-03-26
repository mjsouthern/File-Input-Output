/* 
Writing Data to Files
*/

#include <stdio.h>

int main() {
    FILE *pWrite = fopen("students.dat", "w");
    if (pWrite != NULL) {
        fprintf(pWrite, "John\tDoe\t12345\t3.75\n");
        printf("Successfully written a text in students.dat file");
        fclose(pWrite);
    }
    
    return 0;
}
