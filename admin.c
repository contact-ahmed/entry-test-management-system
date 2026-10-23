
#include <stdio.h>

#define ADMIN_PIN 5656
#define MAX_ATTEMPTS 3


void adminLogin(void);
void adminMenu(void);
void addquestion(void);
void viewquestion(void);
void editquestion(void);
void deletequestion(void);
void viewstudents(void);
void viewresults(void);

int main(void)
{
    int choice;

    do
    {
        printf("\n===== ENTRY TEST MANAGEMENT SYSTEM =====\n");
        printf("1. Admin Login\n");
        printf("2. Exit\n");
        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1)
        {
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF)
            {
            }

            printf("Invalid input!\n");
            continue;
        }

        switch (choice)
        {
            case 1:
                adminLogin();
                break;

            case 2:
                printf("Goodbye!\n");
                break;

            default:
                printf("Invalid choice!\n");
        }

    } while (choice != 2);

    return 0;
}

void adminLogin(void)
{
    int pin;
    int attempts;

    for (attempts = 1; attempts <= MAX_ATTEMPTS; attempts++)
    {
        printf("\n===== ADMIN LOGIN =====\n");
        printf("Enter Admin PIN: ");

        if (scanf("%d", &pin) != 1)
        {
            int ch;

            printf("Invalid input! Enter a number.\n");

            while ((ch = getchar()) != '\n' && ch != EOF)
            {
            }

            attempts--;
            continue;
        }

        if (pin == ADMIN_PIN)
        {
            printf("Login Successful!\n");
            adminMenu();
            return;
        }

        printf("Wrong PIN! Attempts left: %d\n",
               MAX_ATTEMPTS - attempts);
    }

    printf("Too many wrong attempts.\n");
    printf("Returning to main menu.\n");
}

void adminMenu(void)
{
    int choice;

    do
    {
        printf("\n===== ADMIN PANEL =====\n");
        printf("1. Add Question\n");
        printf("2. View Questions\n");
        printf("3. Edit Question\n");
        printf("4. Delete Question\n");
        printf("5. View Registered Students\n");
        printf("6. View Student Results\n");
        printf("7. Logout\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            int ch;

            printf("Invalid input!\n");

            while ((ch = getchar()) != '\n' && ch != EOF)
            {
            }

            continue;
        }

        switch (choice)
        {
            case 1:
                addquestion();
                break;

            case 2:
                viewquestion();
                break;

            case 3:
                editquestion();
                break;

            case 4:
                deletequestion();
                break;

            case 5:
                viewstudents();
                break;

            case 6:
                viewresults();
                break;

            case 7:
                printf("Logging out...\n");
                break;

            default:
                printf("Invalid choice!\n");
        }

    } while (choice != 7);
}

void addquestion(void)
{
    printf("\n===== ADD QUESTION =====\n");
    printf("Add Question will be update soon.\n");
}

void viewquestion(void)
{
    printf("\n===== AVAILABLE QUESTIONS =====\n");

    printf("\nQ1. Who developed the C programming language?\n");
    printf("A) Bjarne Stroustrup\n");
    printf("B) Dennis Ritchie\n");
    printf("C) James Gosling\n");
    printf("D) Charles Babbage\n");
    printf("Correct Answer: B\n");

    printf("\nQ2. Which of the following is a C keyword?\n");
    printf("A) print\n");
    printf("B) loop\n");
    printf("C) while\n");
    printf("D) run\n");
    printf("Correct Answer: C\n");

    printf("\nQ3. Which extension is used for C source files?\n");
    printf("A) .cpp\n");
    printf("B) .java\n");
    printf("C) .c\n");
    printf("D) .py\n");
    printf("Correct Answer: C\n");

    printf("\nQ4. Which function is the entry point of a C program?\n");
    printf("A) start()\n");
    printf("B) main()\n");
    printf("C) begin()\n");
    printf("D) run()\n");
    printf("Correct Answer: B\n");

    printf("\nQ5. Which header file is used for printf()?\n");
    printf("A) stdlib.h\n");
    printf("B) math.h\n");
    printf("C) string.h\n");
    printf("D) stdio.h\n");
    printf("Correct Answer: D\n");
}

void editquestion(void)
{
    printf("\n===== EDIT QUESTION =====\n");
    printf("Edit Question  will be  update soon.\n");
}

void deletequestion(void)
{
    printf("\n===== DELETE QUESTION =====\n");
    printf("Delete Question  will be  update  soon.\n");
}

void viewstudents(void)
{
    printf("\n===== REGISTERED STUDENTS =====\n");
    printf("Student records will be update soon.\n");
}

void viewresults(void)
{
    printf("\n===== STUDENT RESULTS =====\n");
    printf("Student results will be updatess soon.\n");
}
