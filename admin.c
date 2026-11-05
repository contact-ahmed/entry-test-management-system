
#include <stdio.h>
#include<string.h>

#define ADMIN_PIN 5656
#define MAX_ATTEMPTS 3
#define MAX_QUESTIONS 50

char questions[MAX_QUESTIONS][200];
char options[MAX_QUESTIONS][4][100];
char correctAnswer[MAX_QUESTIONS];
int questionCount = 0;


void adminLogin(void);
void adminMenu(void);
void addquestion(void);
void viewquestion(void);
void editquestion(void);
void deletequestion(void);
void viewstudents(void);
void viewresults(void);

void clearInputBuffer(void);
void readline(char str[], int size);
void populateSampleQuestions(void);

int main(void)
{
    int choice;
    populateSampleQuestions();

    do
    {
        printf("\n===== ENTRY TEST MANAGEMENT SYSTEM =====\n");
        printf("1. Admin Login\n");
        printf("2. Exit\n");
        printf("Enter choice: ");



        if (scanf("%d", &choice) != 1)
        {
            clearInputBuffer();

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
            printf("Invalid input! Enter a number.\n");
            clearInputBuffer();
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
            printf("Invalid input!\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

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

void clearInputBuffer(void)
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
    {
    }
}

void readline(char str[], int size)
{
     fgets(str, size, stdin);
     str[strcspn(str, "\n")] = 0; 
   
}

void populateSampleQuestions(void)
{
    strcpy(questions[0], "Who developed the C programming language?");
    strcpy(options[0][0], "Bjarne Stroustrup");
    strcpy(options[0][1], "Dennis Ritchie");
    strcpy(options[0][2], "James Gosling");
    strcpy(options[0][3], "Charles Babbage");
    correctAnswer[0] = 'B';

    strcpy(questions[1], "Which of the following is a C keyword?");
    strcpy(options[1][0], "print");
    strcpy(options[1][1], "loop");
    strcpy(options[1][2], "while");
    strcpy(options[1][3], "run");
    correctAnswer[1] = 'C';

    strcpy(questions[2], "Which extension is used for C source files?");
    strcpy(options[2][0], ".cpp");
    strcpy(options[2][1], ".java");
    strcpy(options[2][2], ".c");
    strcpy(options[2][3], ".py");
    correctAnswer[2] = 'C';

    strcpy(questions[3], "Which function is the entry point of a C program?");
    strcpy(options[3][0], "start()");
    strcpy(options[3][1], "main()");
    strcpy(options[3][2], "begin()");
    strcpy(options[3][3], "run()");
    correctAnswer[3] = 'B';

    strcpy(questions[4], "Which header file is used for printf()?");
    strcpy(options[4][0], "stdlib.h");
    strcpy(options[4][1], "math.h");
    strcpy(options[4][2], "string.h");
    strcpy(options[4][3], "stdio.h");
    correctAnswer[4] = 'D';

    questionCount = 5;
}

void addquestion(void)
{
    int i;
    char ans[10];
    printf("\n===== ADD QUESTION =====\n");
    if (questionCount >= MAX_QUESTIONS)
    {
        printf("Cannot add more questions. Maximum limit reached.\n");
        return;
    }
    printf("Enter New Questions: ");
    readline(questions[questionCount], 200);

    for(i = 0; i < 4; i++)
    {
        printf("Enter Option %c: ", 'A' + i);
        readline(options[questionCount][i], 100);
    }

    do
    {
       printf("Enter Correct Answer (A/B/C/D): ");
       readline(ans, 10);
       if(ans[0] >= 'a' && ans[0] <= 'd')
       {
           ans[0] = ans[0] - 32; 
       }
    } while (ans[0] < 'A' || ans[0] > 'D' || ans[1] != '\0');
    correctAnswer[questionCount] = ans[0];
    questionCount++;

    printf("Question added successfully!\n");

    
}

void viewquestion(void)
{
    int i, j;
    printf("\n===== AVAILABLE QUESTIONS =====\n");
    if (questionCount == 0)
    {
        printf("No questions available.\n");
        return;
    }
    for (i = 0; i < questionCount; i++)
    {
        printf("\nQuestion %d: %s\n", i + 1, questions[i]);
        for (j = 0; j < 4; j++)
        {
            printf("%c) %s\n", 'A' + j, options[i][j]);
        }
        printf("Correct Answer: %c\n", correctAnswer[i]);
    }


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
    printf("Student results will be updated soon.\n");
}
