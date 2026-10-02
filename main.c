#include <stdio.h>

#include "student.h"
#include "admin.h"

int main()
{
    int choice;

    do
    {
        printf("\n========================================\n");
        printf("      ENTRY TEST MANAGEMENT SYSTEM\n");
        printf("========================================\n");

        printf("\n1. Register Student");
        printf("\n2. Student Login");
        printf("\n3. Admin Login");
        printf("\n4. Exit");

        printf("\n\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice)
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
                printf("Program Closed.\n");
                break;

            default:
                printf("\nInvalid choice! Please select 1-4.\n");
        }

    } while(choice != 4);

    return 0;
}