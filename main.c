#include <stdio.h>
#include "student.h"
#include "admin.h"
#include "question.h"

int main(void)
{
    int choice;

    loadStudents();
    loadQuestions();

    do
    {
        printf("\n========================================\n");
        printf("      ENTRY TEST MANAGEMENT SYSTEM\n");
        printf("========================================\n");
        printf("1. Register Student\n");
        printf("2. Student Login\n");
        printf("3. Admin Login\n");
        printf("4. Exit\n");
        printf("\nEnter your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) {}
            printf("\nInvalid input! Please enter a number from 1 to 4.\n");
            continue;
        }

        /* Consume the newline left by scanf before calling line-based menus. */
        {
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) {}
        }

        switch (choice)
        {
            case 1:
                registerStudent();
                break;
            case 2:
                studentLogin();
                break;
            case 3:
                adminLogin();
                break;
            case 4:
                printf("\nThank you for using Entry Test Management System.\n");
                printf("Program closed.\n");
                break;
            default:
                printf("\nInvalid choice! Please select 1-4.\n");
        }
    } while (choice != 4);

    freeQuestions();
    return 0;
}