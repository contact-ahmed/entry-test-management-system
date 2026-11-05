
#include <stdio.h>
#include <string.h>
#include "student.h"

#define MAX_STUDENTS 100

char studentName[MAX_STUDENTS][50];
char studentUsername[MAX_STUDENTS][30];
char studentPassword[MAX_STUDENTS][30];
int studentIDs[MAX_STUDENTS];

int totalStudents = 0;
int currentStudentIndex = -1;

void saveStudents(void);
void loadStudents(void);

void registerStudent(void)
{
    char names[50];
    char usernames[30];
    char passwords[30];
    int i;

    printf("\n====== STUDENT REGISTRATION ======\n");

    if (totalStudents >= MAX_STUDENTS)
    {
        printf("Registration limit reached. Cannot register.\n");
        return;
    }

    printf("Enter Student Name: ");
    scanf(" %49[^\n]", names);

    printf("Create a Username: ");
    scanf("%29s", usernames);

    // Check if username already exists
    for (i = 0; i < totalStudents; i++)
    {
        if (strcmp(studentUsername[i], usernames) == 0)
        {
            printf("Username already exists. Please choose another.\n");
            return;
        }
    }

    printf("Create a Password: ");
    scanf("%29s", passwords);

    studentIDs[totalStudents] = 1001 + totalStudents;

    strcpy(studentName[totalStudents], names);
    strcpy(studentUsername[totalStudents], usernames);
    strcpy(studentPassword[totalStudents], passwords);

    printf("\nRegistration Successful!\n");
    printf("Your Student ID is: %d\n", studentIDs[totalStudents]);

    totalStudents++;

    saveStudents();
}

void studentLogin(void)
{
    char username[30];
    char password[30];
    int i;
    int found = 0;

    printf("\n====== STUDENT LOGIN ======\n");

    if (totalStudents == 0)
    {
        printf("No registered students found. Please register first.\n");
        return;
    }

    printf("Enter Username: ");
    scanf("%29s", username);

    printf("Enter Password: ");
    scanf("%29s", password);

    for (i = 0; i < totalStudents; i++)
    {
        if (strcmp(studentUsername[i], username) == 0 &&
            strcmp(studentPassword[i], password) == 0)
        {
            found = 1;
            currentStudentIndex = i;
            break;
        }
    }

    if (found == 1)
    {
        printf("\nLogin Successful! Welcome %s\n",
               studentName[currentStudentIndex]);

        studentMenu();

        currentStudentIndex = -1;
    }
    else
    {
        printf("Invalid Username or Password.\n");
    }
}

void studentMenu(void)
{
    int choice;

    do
    {
        printf("\n====== STUDENT MENU ======\n");
        printf("1. Take Test\n");
        printf("2. View My Results\n");
        printf("3. View My Profile\n");
        printf("4. Logout\n");

        printf("Enter Your Choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                printf("Take Test Selected\n");
                break;

            case 2:
                printf("View My Results Selected\n");
                break;

            case 3:
                ViewMyProfile();
                break;

            case 4:
                printf("\nLogged out successfully!\n");
                break;

            default:
                printf("\nInvalid choice! Please select 1-4.\n");
        }

    } while (choice != 4);
}

// View student profile
void ViewMyProfile(void)
{
    if (currentStudentIndex == -1)
    {
        printf("\nPlease log in first!\n");
        return;
    }

    printf("\n====== MY PROFILE ======\n");
    printf("Student ID: %d\n", studentIDs[currentStudentIndex]);
    printf("Name: %s\n", studentName[currentStudentIndex]);
    printf("Username: %s\n", studentUsername[currentStudentIndex]);
}

void saveStudents(void)
{
    FILE *fp;

    fp = fopen("students.txt", "w");

    if (fp == NULL)
    {
        printf("Error opening student file!\n");
        return;
    }

    for (int i = 0; i < totalStudents; i++)
    {
        fprintf(fp, "%d\n%s\n%s\n%s\n",
                studentIDs[i],
                studentName[i],
                studentUsername[i],
                studentPassword[i]);
    }

    fclose(fp);

    printf("Student data saved successfully!\n");
}

void loadStudents(void)
{
    FILE *fp;

    fp = fopen("students.txt", "r");

    if (fp == NULL)
    {
        return;
    }

    while (totalStudents < MAX_STUDENTS &&
           fscanf(fp, "%d\n%49[^\n]\n%29s\n%29s\n",
                  &studentIDs[totalStudents],
                  studentName[totalStudents],
                  studentUsername[totalStudents],
                  studentPassword[totalStudents]) == 4)
    {
        totalStudents++;
    }

    fclose(fp);

    printf("Student data loaded successfully!\n");
}