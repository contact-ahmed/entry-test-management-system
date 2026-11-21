#include <stdio.h>
#include <string.h>
#include "student.h"
#include "test.h"

#define MAX_STUDENTS 100
#define STUDENTS_FILE "students.txt"
#define RESULTS_FILE "results.txt"

/* Student records */
char studentName[MAX_STUDENTS][50];
char studentUsername[MAX_STUDENTS][30];
char studentPassword[MAX_STUDENTS][30];
int studentIDs[MAX_STUDENTS];

int totalStudents = 0;
int currentStudentIndex = -1;

/* Private helper functions */
static void clearInputBuffer(void);
static int usernameExists(const char username[]);
static void viewMyResults(void);

/* Remove any extra characters left in the input buffer */
static void clearInputBuffer(void)
{
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF)
    {
    }
}

/* Check whether a username is already registered */
static int usernameExists(const char username[])
{
    int i;

    for (i = 0; i < totalStudents; i++)
    {
        if (strcmp(studentUsername[i], username) == 0)
        {
            return 1;
        }
    }

    return 0;
}

/* Student Registration */
void registerStudent(void)
{
    char name[50];
    char username[30];
    char password[30];

    printf("\n====== STUDENT REGISTRATION ======\n");

    if (totalStudents >= MAX_STUDENTS)
    {
        printf("Registration limit reached. Cannot register more students.\n");
        return;
    }

    printf("Enter Student Name: ");
    if (scanf(" %49[^\n]", name) != 1)
    {
        printf("Invalid name. Registration cancelled.\n");
        return;
    }

    printf("Create a Username: ");
    if (scanf("%29s", username) != 1)
    {
        printf("Invalid username. Registration cancelled.\n");
        return;
    }

    if (usernameExists(username))
    {
        printf("Username already exists. Please choose another.\n");
        return;
    }

    printf("Create a Password: ");
    if (scanf("%29s", password) != 1)
    {
        printf("Invalid password. Registration cancelled.\n");
        return;
    }

    /* Assign an ID and store the new student's details */
    studentIDs[totalStudents] = 1001 + totalStudents;

    strcpy(studentName[totalStudents], name);
    strcpy(studentUsername[totalStudents], username);
    strcpy(studentPassword[totalStudents], password);

    totalStudents++;

    /* Save all registered students so records remain after program exit */
    saveStudents();

    printf("\nRegistration Successful!\n");
    printf("Your Student ID is: %d\n", studentIDs[totalStudents - 1]);
}

/* Student Login */
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
    if (scanf("%29s", username) != 1)
    {
        printf("Invalid username.\n");
        return;
    }

    printf("Enter Password: ");
    if (scanf("%29s", password) != 1)
    {
        printf("Invalid password.\n");
        return;
    }

    /* Match the entered credentials with saved student records */
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
        printf("\nLogin Successful! Welcome, %s.\n",
               studentName[currentStudentIndex]);

        studentMenu();

        /* Clear the active session after logout */
        currentStudentIndex = -1;
    }
    else
    {
        printf("\nInvalid Username or Password.\n");
    }
}

/* Student Menu */
void studentMenu(void)
{
    int choice;

    if (currentStudentIndex == -1)
    {
        printf("\nPlease log in first.\n");
        return;
    }

    do
    {
        printf("\n====== STUDENT MENU ======\n");
        printf("1. Take Test\n");
        printf("2. View My Results\n");
        printf("3. View My Profile\n");
        printf("4. Logout\n");
        printf("Enter Your Choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("\nInvalid input! Please enter a number from 1 to 4.\n");
            clearInputBuffer();
            continue;
        }

        switch (choice)
        {
            case 1:
                /* Pass the logged-in student's ID to the test module */
                takeTest(studentIDs[currentStudentIndex]);
                break;

            case 2:
                viewMyResults();
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

/* View the profile of the currently logged-in student */
void ViewMyProfile(void)
{
    if (currentStudentIndex == -1)
    {
        printf("\nPlease log in first!\n");
        return;
    }

    printf("\n====== MY PROFILE ======\n");
    printf("Student ID : %d\n", studentIDs[currentStudentIndex]);
    printf("Name       : %s\n", studentName[currentStudentIndex]);
    printf("Username   : %s\n", studentUsername[currentStudentIndex]);
}

/* Display only the results belonging to the logged-in student */
static void viewMyResults(void)
{
    FILE *fp;
    int studentID;
    int score;
    int total;
    float percentage;
    int found = 0;

    if (currentStudentIndex == -1)
    {
        printf("\nPlease log in first!\n");
        return;
    }

    fp = fopen(RESULTS_FILE, "r");

    printf("\n====== MY TEST RESULTS ======\n");

    if (fp == NULL)
    {
        printf("You have not attempted any tests yet.\n");
        return;
    }

    while (fscanf(fp, "%d|%d|%d|%f",
                  &studentID, &score, &total, &percentage) == 4)
    {
        if (studentID == studentIDs[currentStudentIndex])
        {
            found = 1;
            printf("\nStudent ID      : %d\n", studentID);
            printf("Correct Answers : %d\n", score);
            printf("Total Questions : %d\n", total);
            printf("Percentage      : %.1f%%\n", percentage);

            if (percentage >= 50.0f)
                printf("Status          : PASS\n");
            else
                printf("Status          : NEEDS IMPROVEMENT\n");
        }
    }

    fclose(fp);

    if (!found)
    {
        printf("You have not attempted any tests yet.\n");
    }
}

/* Save all student records to the data file */
void saveStudents(void)
{
    FILE *fp;
    int i;

    fp = fopen(STUDENTS_FILE, "w");

    if (fp == NULL)
    {
        printf("\nError: Could not save student records.\n");
        return;
    }

    for (i = 0; i < totalStudents; i++)
    {
        fprintf(fp, "%d\n%s\n%s\n%s\n",
                studentIDs[i],
                studentName[i],
                studentUsername[i],
                studentPassword[i]);
    }

    fclose(fp);
}

/* Load student records when the program starts */
void loadStudents(void)
{
    FILE *fp;

    fp = fopen(STUDENTS_FILE, "r");

    if (fp == NULL)
    {
        /* The file will be created automatically on first registration */
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
