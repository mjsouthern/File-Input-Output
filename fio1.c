/* 
Reading Data from Files
*/

#include <stdio.h>

int main() {
    FILE *pRead = fopen("names.dat", "r");
    if (pRead == NULL) {
        printf("File cannot be opened\n");
    } else {
        char firstName[20], lastName[20];
        int id;
        
        while (fscanf(pRead, "%s %s %d", firstName, lastName, &id) == 3) {
            printf("%s %s %d\n", firstName, lastName, id);
        }        
        fclose(pRead);
    }

    return 0;
}
