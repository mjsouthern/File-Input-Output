#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100

typedef struct {
    int id;
    char firstName[30];
    char middleName[30];
    char lastName[30];
    float english, filipino, math, science, average;
} Student;


void addStudentRecord();
void viewStudentRecords();
void searchStudentByLastName();
void editStudentRecord();
void deleteStudentRecord();

void saveStudentsToFile(Student students[], int count);
int loadStudentsFromFile(Student students[]);

int main() {
    int choice;

    do {
        printf("\n------- Student Grading Sheet System (coded by @MJSouthernDev96) -------\n");
        printf("1. Add Student Record\n");
        printf("2. View All Records\n");
        printf("3. Search by Last Name\n");
        printf("4. Edit Student Record\n");
        printf("5. Delete Student Record\n");
        printf("6. Exit\n\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // clear newline from input buffer

        switch (choice) {
            case 1: addStudentRecord(); break;
            case 2: viewStudentRecords(); break;
            case 3: searchStudentByLastName(); break;
            case 4: editStudentRecord(); break;
            case 5: deleteStudentRecord(); break;
            case 6: printf("Exiting program.\n"); break;
            default: printf("Invalid choice. Try again.\n");
        }
    } while (choice != 6);

    return 0;
}

void addStudentRecord() {
    FILE *file;
    int fileExists = 1;

    file = fopen("grades.csv", "r");
    if (file == NULL) fileExists = 0;
    else fclose(file);

    file = fopen("grades.csv", "a");
    if (file == NULL) {
        perror("Error opening grades.csv");
        return;
    }

    if (!fileExists) {
        fprintf(file, "First Name,Middle Name,Last Name,English,Filipino,Math,Science,Average\n");
    }

    Student s;

    printf("\nEnter First Name: ");
    fgets(s.firstName, sizeof(s.firstName), stdin);
    s.firstName[strcspn(s.firstName, "\n")] = '\0';

    printf("Enter Middle Name: ");
    fgets(s.middleName, sizeof(s.middleName), stdin);
    s.middleName[strcspn(s.middleName, "\n")] = '\0';

    printf("Enter Last Name: ");
    fgets(s.lastName, sizeof(s.lastName), stdin);
    s.lastName[strcspn(s.lastName, "\n")] = '\0';

    printf("\n");
    printf("Enter grade for English: ");
    scanf("%f", &s.english);
    printf("Enter grade for Filipino: ");
    scanf("%f", &s.filipino);
    printf("Enter grade for Math: ");
    scanf("%f", &s.math);
    printf("Enter grade for Science: ");
    scanf("%f", &s.science);
    getchar();

    s.average = (s.english + s.filipino + s.math + s.science) / 4.0;

    printf("\n------Student Summary:------\n");
    printf("Name     : %s %s %s\n", s.firstName, s.middleName, s.lastName);
    printf("English  : %.2f\n", s.english);
    printf("Filipino : %.2f\n", s.filipino);
    printf("Math     : %.2f\n", s.math);
    printf("Science  : %.2f\n", s.science);
    printf("Average  : %.2f\n", s.average);

    fprintf(file, "\"%s\",\"%s\",\"%s\",%.2f,%.2f,%.2f,%.2f,%.2f\n",
            s.firstName, s.middleName, s.lastName,
            s.english, s.filipino, s.math, s.science, s.average);

    printf("Record saved successfully.\n");
    fclose(file);
}

void viewStudentRecords() {
    FILE *file = fopen("grades.csv", "r");
    if (file == NULL) {
        printf("No records found.\n");
        return;
    }

    Student s;
    char line[256];

    // Read and skip the header
    fgets(line, sizeof(line), file);

    printf("\nStudent Records:\n\n");
    printf("%-15s %-15s %-15s %7s %9s %7s %9s %8s\n", 
           "First Name", "Middle Name", "Last Name",
           "English", "Filipino", "Math", "Science", "Average");
    printf("-------------------------------------------------------------------------------------\n");

    int count = 0;
    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "\"%[^\"]\",\"%[^\"]\",\"%[^\"]\",%f,%f,%f,%f,%f",
                   s.firstName, s.middleName, s.lastName,
                   &s.english, &s.filipino, &s.math, &s.science, &s.average) == 8) {
            printf("%-15s %-15s %-15s %7.2f %9.2f %7.2f %9.2f %8.2f%%\n",
                   s.firstName, s.middleName, s.lastName,
                   s.english, s.filipino, s.math, s.science, s.average);
            count++;
        }
    }

    if (count == 0) {
        printf("No student records found.\n");
    }

    fclose(file);
}

void searchStudentByLastName() {
    FILE *file = fopen("grades.csv", "r");
    if (file == NULL) {
        printf("No records found.\n");
        return;
    }

    char search[30], line[256];
    Student s;
    int found = 0;

    printf("Enter last name to search: ");
    fgets(search, sizeof(search), stdin);
    search[strcspn(search, "\n")] = '\0'; // Remove newline

    // Read and skip the header
    fgets(line, sizeof(line), file);

    printf("\nSearch Results for '%s':\n\n", search);
    printf("%-15s %-15s %-15s %7s %9s %7s %9s %8s\n", 
           "First Name", "Middle Name", "Last Name",
           "English", "Filipino", "Math", "Science", "Average");
    printf("-------------------------------------------------------------------------------------\n");

    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "\"%[^\"]\",\"%[^\"]\",\"%[^\"]\",%f,%f,%f,%f,%f",
                   s.firstName, s.middleName, s.lastName,
                   &s.english, &s.filipino, &s.math, &s.science, &s.average) == 8) {

            if (strcasecmp(s.lastName, search) == 0) {
                printf("%-15s %-15s %-15s %7.2f %9.2f %7.2f %9.2f %8.2f%%\n",
                       s.firstName, s.middleName, s.lastName,
                       s.english, s.filipino, s.math, s.science, s.average);
                found = 1;
            }
        }
    }

    if (!found) {
        printf("No student records found for last name '%s'.\n", search);
    }

    fclose(file);
}

void editStudentRecord() {
    Student students[MAX_STUDENTS];
    int count = loadStudentsFromFile(students);

    if (count == 0) {
        printf("No records to edit.\n");
        return;
    }

    char search[30];
    printf("Enter last name of student to edit: ");
    fgets(search, sizeof(search), stdin);
    search[strcspn(search, "\n")] = '\0';

    printf("\n");
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcasecmp(students[i].lastName, search) == 0) {
            found = 1;
            printf("Editing record for %s %s %s:\n\n", students[i].firstName, students[i].middleName, students[i].lastName);

            printf("Enter new English grade: ");
            scanf("%f", &students[i].english);
            printf("Enter new Filipino grade: ");
            scanf("%f", &students[i].filipino);
            printf("Enter new Math grade: ");
            scanf("%f", &students[i].math);
            printf("Enter new Science grade: ");
            scanf("%f", &students[i].science);
            getchar();

            students[i].average = (students[i].english + students[i].filipino +
                                   students[i].math + students[i].science) / 4.0;

            printf("\nRecord updated successfully.\n");
            break;
        }
    }

    if (found)
        saveStudentsToFile(students, count);
    else
        printf("No student found with last name '%s'\n", search);
}

void deleteStudentRecord() {
    Student students[MAX_STUDENTS];
    int count = loadStudentsFromFile(students);

    if (count == 0) {
        printf("No records to delete.\n");
        return;
    }

    char search[30];
    printf("Enter last name of student to delete: ");
    fgets(search, sizeof(search), stdin);
    search[strcspn(search, "\n")] = '\0';

    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcasecmp(students[i].lastName, search) == 0) {
            found = 1;
            for (int j = i; j < count - 1; j++) {
                students[j] = students[j + 1];  // shift left
            }
            count--;
            printf("\nRecord successfully deleted.\n");
            break;
        }
    }

    if (found)
        saveStudentsToFile(students, count);
    else
        printf("No student found with last name '%s'\n", search);
}

int loadStudentsFromFile(Student students[]) {
    FILE *file = fopen("grades.csv", "r");
    if (file == NULL) return 0;

    char line[256];
    int count = 0;

    fgets(line, sizeof(line), file); // skip header
    while (fgets(line, sizeof(line), file) && count < MAX_STUDENTS) {
        if (sscanf(line, "\"%[^\"]\",\"%[^\"]\",\"%[^\"]\",%f,%f,%f,%f,%f",
                   students[count].firstName, students[count].middleName, students[count].lastName,
                   &students[count].english, &students[count].filipino,
                   &students[count].math, &students[count].science, &students[count].average) == 8) {
            count++;
        }
    }

    fclose(file);
    return count;
}

void saveStudentsToFile(Student students[], int count) {
    FILE *file = fopen("grades.csv", "w");
    if (file == NULL) {
        perror("Error writing file");
        return;
    }

    fprintf(file, "First Name,Middle Name,Last Name,English,Filipino,Math,Science,Average\n");
    for (int i = 0; i < count; i++) {
        fprintf(file, "\"%s\",\"%s\",\"%s\",%.2f,%.2f,%.2f,%.2f,%.2f\n",
                students[i].firstName, students[i].middleName, students[i].lastName,
                students[i].english, students[i].filipino, students[i].math,
                students[i].science, students[i].average);
    }

    fclose(file);
}