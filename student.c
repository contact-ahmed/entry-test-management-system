#include <stdio.h>
#include <string.h>
#include "student.h"
#include "test.h"
#include "result.h"

#define MAX_STUDENTS 100
#define STUDENTS_FILE "students.txt"

char studentName[MAX_STUDENTS][50];
char studentUsername[MAX_STUDENTS][30];
char studentPassword[MAX_STUDENTS][30];
int studentIDs[MAX_STUDENTS];
int totalStudents = 0;
int currentStudentIndex = -1;

static void clearInputBuffer(void);
static int usernameExists(const char username[]);

static void clearInputBuffer(void)
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {}
}

static int usernameExists(const char username[])
{
    int i;

    for (i = 0; i < totalStudents; i++)
    {
        if (strcmp(studentUsername[i], username) == 0)
            return 1;
    }

    return 0;
}

void registerStudent(void)
{
    char name[50], username[30], password[30];

    printf("\n========== STUDENT REGISTRATION ==========\n");

    if (totalStudents >= MAX_STUDENTS)
    {
        printf("The student limit has been reached.\n");
        return;
    }

    printf("Enter student name: ");
    if (scanf(" %49[^\n]", name) != 1)
    {
        printf("Invalid name.\n");
        clearInputBuffer();
        return;
    }

    printf("Create username: ");
    if (scanf("%29s", username) != 1)
    {
        printf("Invalid username.\n");
        clearInputBuffer();
        return;
    }

    if (usernameExists(username))
    {
        printf("That username is already taken.\n");
        clearInputBuffer();
        return;
    }

    printf("Create password: ");
    if (scanf("%29s", password) != 1)
    {
        printf("Invalid password.\n");
        clearInputBuffer();
        return;
    }

    studentIDs[totalStudents] = 1001 + totalStudents;
    strcpy(studentName[totalStudents], name);
    strcpy(studentUsername[totalStudents], username);
    strcpy(studentPassword[totalStudents], password);
    totalStudents++;

    saveStudents();

    printf("\nRegistration successful!\n");
    printf("Your student ID is: %d\n", studentIDs[totalStudents - 1]);
}

void studentLogin(void)
{
    char username[30], password[30];
    int i, found = 0;

    printf("\n========== STUDENT LOGIN ==========\n");

    if (totalStudents == 0)
    {
        printf("No students are registered yet.\n");
        return;
    }

    printf("Username: ");
    if (scanf("%29s", username) != 1)
    {
        printf("Invalid username.\n");
        clearInputBuffer();
        return;
    }

    printf("Password: ");
    if (scanf("%29s", password) != 1)
    {
        printf("Invalid password.\n");
        clearInputBuffer();
        return;
    }

    for (i = 0; i < totalStudents; i++)
    {
        if (strcmp(studentUsername[i], username) == 0 &&
            strcmp(studentPassword[i], password) == 0)
        {
            currentStudentIndex = i;
            found = 1;
            break;
        }
    }

    if (found)
    {
        printf("\nWelcome, %s!\n", studentName[currentStudentIndex]);
        studentMenu();
        currentStudentIndex = -1;
    }
    else
    {
        printf("Incorrect username or password.\n");
    }
}

void studentMenu(void)
{
    int choice;

    if (currentStudentIndex == -1)
    {
        printf("Please log in first.\n");
        return;
    }

    do
    {
        printf("\n========== STUDENT MENU ==========\n");
        printf("1. Take Test\n");
        printf("2. View My Results\n");
        printf("3. View My Profile\n");
        printf("4. Logout\n");
        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Please enter a number from 1 to 4.\n");
            clearInputBuffer();
            continue;
        }

        switch (choice)
        {
            case 1:
                clearInputBuffer();
                takeTest(studentIDs[currentStudentIndex]);
                break;
            case 2:
                viewStudentResults(studentIDs[currentStudentIndex]);
                break;
            case 3:
                ViewMyProfile();
                break;
            case 4:
                printf("You have been logged out.\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 4);
}

void ViewMyProfile(void)
{
    if (currentStudentIndex == -1)
    {
        printf("Please log in first.\n");
        return;
    }

    printf("\n========== MY PROFILE ==========\n");
    printf("Student ID : %d\n", studentIDs[currentStudentIndex]);
    printf("Name       : %s\n", studentName[currentStudentIndex]);
    printf("Username   : %s\n", studentUsername[currentStudentIndex]);
}

void saveStudents(void)
{
    FILE *fp;
    int i;

    fp = fopen(STUDENTS_FILE, "w");
    if (fp == NULL)
    {
        printf("Could not save student records.\n");
        return;
    }

    for (i = 0; i < totalStudents; i++)
    {
        fprintf(fp, "%d\n%s\n%s\n%s\n",
                studentIDs[i], studentName[i],
                studentUsername[i], studentPassword[i]);
    }

    fclose(fp);
}

void loadStudents(void)
{
    FILE *fp;

    fp = fopen(STUDENTS_FILE, "r");
    if (fp == NULL)
    {
        totalStudents = 0;
        return;
    }

    totalStudents = 0;

    while (totalStudents < MAX_STUDENTS &&
           fscanf(fp, "%d\n%49[^\n]\n%29s\n%29s",
                  &studentIDs[totalStudents],
                  studentName[totalStudents],
                  studentUsername[totalStudents],
                  studentPassword[totalStudents]) == 4)
    {
        totalStudents++;
    }

    fclose(fp);
}