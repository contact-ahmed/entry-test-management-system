#include <stdio.h>
#include <string.h>
#include "admin.h"
#include "question.h"
#include "result.h"

#define ADMIN_PIN 5656
#define MAX_ATTEMPTS 3
#define STUDENTS_FILE "students.txt"

static int readLine(char text[], int size)
{
    int ch;
    size_t length;

    if (fgets(text, size, stdin) == NULL)
        return 0;

    length = strlen(text);
    if (length > 0 && text[length - 1] == '\n')
        text[length - 1] = '\0';
    else
    {
        while ((ch = getchar()) != '\n' && ch != EOF) {}
    }

    return 1;
}

static int readNumber(const char *message, int *number)
{
    char line[30];
    char extra;

    printf("%s", message);
    if (!readLine(line, sizeof(line)))
        return 0;

    return sscanf(line, " %d %c", number, &extra) == 1;
}

void adminLogin(void)
{
    int pin, attempts;

    for (attempts = 1; attempts <= MAX_ATTEMPTS; attempts++)
    {
        if (!readNumber("\n===== ADMIN LOGIN =====\nEnter Admin PIN: ", &pin))
        {
            printf("Please enter a numeric PIN.\n");
            attempts--;
            continue;
        }

        if (pin == ADMIN_PIN)
        {
            printf("Login successful!\n");
            adminMenu();
            return;
        }

        printf("Incorrect PIN. Attempts remaining: %d\n",
               MAX_ATTEMPTS - attempts);
    }

    printf("Too many incorrect attempts. Returning to main menu.\n");
}

void adminMenu(void)
{
    int choice;

    do
    {
        printf("\n========== ADMIN PANEL ==========\n");
        printf("1. Add Question\n");
        printf("2. View Questions\n");
        printf("3. Edit Question\n");
        printf("4. Delete Question\n");
        printf("5. View Registered Students\n");
        printf("6. View Student Results\n");
        printf("7. Logout\n");

        if (!readNumber("Enter your choice: ", &choice))
        {
            printf("Invalid input. Enter a number from 1 to 7.\n");
            continue;
        }

        switch (choice)
        {
            case 1: addquestion(); break;
            case 2: viewquestion(); break;
            case 3: editquestion(); break;
            case 4: deletequestion(); break;
            case 5: viewStudents(); break;
            case 6: viewAllResults(); break;
            case 7: printf("Admin logged out.\n"); break;
            default: printf("Invalid choice. Please select 1-7.\n");
        }
    } while (choice != 7);
}

static void viewStudents(void)
{
    FILE *fp;
    int id, count = 0;
    char name[50], username[30], password[30];

    printf("\n========== REGISTERED STUDENTS ==========\n");

    fp = fopen(STUDENTS_FILE, "r");
    if (fp == NULL)
    {
        printf("No student records found yet.\n");
        return;
    }

    printf("%-10s %-25s %-20s\n", "ID", "NAME", "USERNAME");
    printf("-------------------------------------------------------\n");

    while (fscanf(fp, "%d\n%49[^\n]\n%29s\n%29s",
                  &id, name, username, password) == 4)
    {
        printf("%-10d %-25.25s %-20s\n", id, name, username);
        count++;
    }

    fclose(fp);

    if (count == 0)
        printf("No valid student records found.\n");
    else
        printf("\nTotal registered students: %d\n", count);
}