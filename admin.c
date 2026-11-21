#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "admin.h"

#define ADMIN_PIN 5656
#define MAX_ATTEMPTS 3
#define MAX_QUESTIONS 50
#define QUESTIONS_FILE "questions.txt"
#define STUDENTS_FILE "students.txt"
#define RESULTS_FILE "results.txt"

char questions[MAX_QUESTIONS][200];
char options[MAX_QUESTIONS][4][100];
char correctAnswer[MAX_QUESTIONS];
int questionCount = 0;

/* Student records are maintained by student.c. */
extern char studentName[][50];
extern char studentUsername[][30];
extern int studentIDs[];
extern int totalStudents;

static void clearInputBuffer(void);
static int readLine(char text[], int size);
static int readNumber(const char *prompt, int *number);
static void setSampleQuestions(void);
static void saveQuestions(void);
static void editquestion(void);
static void deletequestion(void);
static void viewstudents(void);
static void viewresults(void);

void loadQuestions(void)
{
    FILE *fp;
    char line[256];
    int i, j;
    char answer;

    fp = fopen(QUESTIONS_FILE, "r");
    if (fp == NULL)
    {
        setSampleQuestions();
        saveQuestions();
        return;
    }

    questionCount = 0;
    while (questionCount < MAX_QUESTIONS)
    {
        if (fgets(line, sizeof(line), fp) == NULL) break;
        line[strcspn(line, "\r\n")] = '\0';
        if (strlen(line) == 0) break;
        strcpy(questions[questionCount], line);

        for (j = 0; j < 4; j++)
        {
            if (fgets(line, sizeof(line), fp) == NULL) break;
            line[strcspn(line, "\r\n")] = '\0';
            strcpy(options[questionCount][j], line);
        }
        if (j != 4) break;

        if (fgets(line, sizeof(line), fp) == NULL) break;
        answer = (char)toupper((unsigned char)line[0]);
        if (answer < 'A' || answer > 'D') break;

        correctAnswer[questionCount] = answer;
        questionCount++;
    }

    fclose(fp);

    if (questionCount == 0)
    {
        setSampleQuestions();
        saveQuestions();
    }
}

static void setSampleQuestions(void)
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

static void saveQuestions(void)
{
    FILE *fp;
    int i, j;

    fp = fopen(QUESTIONS_FILE, "w");
    if (fp == NULL)
    {
        printf("Error: Could not save the question bank.\n");
        return;
    }

    for (i = 0; i < questionCount; i++)
    {
        fprintf(fp, "%s\n", questions[i]);
        for (j = 0; j < 4; j++)
            fprintf(fp, "%s\n", options[i][j]);
        fprintf(fp, "%c\n", correctAnswer[i]);
    }

    fclose(fp);
}

static void clearInputBuffer(void)
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {}
}

/* Reads one complete line and removes the newline. */
static int readLine(char text[], int size)
{
    size_t length;
    int ch;

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

static int readNumber(const char *prompt, int *number)
{
    char line[40];
    char extra;

    printf("%s", prompt);
    if (!readLine(line, sizeof(line)))
        return 0;

    if (sscanf(line, " %d %c", number, &extra) != 1)
        return 0;

    return 1;
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
            case 5: viewstudents(); break;
            case 6: viewresults(); break;
            case 7: printf("Admin logged out.\n"); break;
            default: printf("Invalid choice. Please select 1-7.\n");
        }
    } while (choice != 7);
}

void addquestion(void)
{
    int i;
    char answer[20];

    printf("\n========== ADD QUESTION ==========\n");
    if (questionCount >= MAX_QUESTIONS)
    {
        printf("Question bank is full. Maximum is %d questions.\n", MAX_QUESTIONS);
        return;
    }

    printf("Enter question: ");
    if (!readLine(questions[questionCount], sizeof(questions[questionCount])) ||
        questions[questionCount][0] == '\0')
    {
        printf("Question cannot be empty.\n");
        return;
    }

    for (i = 0; i < 4; i++)
    {
        printf("Enter option %c: ", 'A' + i);
        if (!readLine(options[questionCount][i], sizeof(options[questionCount][i])) ||
            options[questionCount][i][0] == '\0')
        {
            printf("Options cannot be empty. Question was not added.\n");
            return;
        }
    }

    do
    {
        printf("Correct answer (A/B/C/D): ");
        if (!readLine(answer, sizeof(answer)))
            return;
        if (strlen(answer) == 1)
            answer[0] = (char)toupper((unsigned char)answer[0]);
        if (strlen(answer) != 1 || answer[0] < 'A' || answer[0] > 'D')
            printf("Please enter only A, B, C or D.\n");
    } while (strlen(answer) != 1 || answer[0] < 'A' || answer[0] > 'D');

    correctAnswer[questionCount] = answer[0];
    questionCount++;
    saveQuestions();
    printf("Question added and saved successfully.\n");
}

void viewquestion(void)
{
    int i, j;

    printf("\n========== QUESTION BANK (%d) ==========\n", questionCount);
    if (questionCount == 0)
    {
        printf("No questions are available.\n");
        return;
    }

    for (i = 0; i < questionCount; i++)
    {
        printf("\nQuestion %d: %s\n", i + 1, questions[i]);
        for (j = 0; j < 4; j++)
            printf("%c) %s\n", 'A' + j, options[i][j]);
        printf("Correct answer: %c\n", correctAnswer[i]);
    }
}

static void editquestion(void)
{
    int number, i;
    char answer[20];
    char newQuestion[200];
    char newOptions[4][100];

    printf("\n========== EDIT QUESTION ==========\n");
    if (questionCount == 0)
    {
        printf("There are no questions to edit.\n");
        return;
    }

    viewquestion();
    if (!readNumber("\nEnter question number to edit: ", &number) ||
        number < 1 || number > questionCount)
    {
        printf("Invalid question number.\n");
        return;
    }

    number--;
    printf("Enter replacement question: ");
    if (!readLine(newQuestion, sizeof(newQuestion)) || newQuestion[0] == '\0')
    {
        printf("Question cannot be empty. No changes made.\n");
        return;
    }

    for (i = 0; i < 4; i++)
    {
        printf("Enter replacement option %c: ", 'A' + i);
        if (!readLine(newOptions[i], sizeof(newOptions[i])) || newOptions[i][0] == '\0')
        {
            printf("Options cannot be empty. No changes made.\n");
            return;
        }
    }

    do
    {
        printf("Enter replacement correct answer (A/B/C/D): ");
        if (!readLine(answer, sizeof(answer)))
            return;
        if (strlen(answer) == 1)
            answer[0] = (char)toupper((unsigned char)answer[0]);
        if (strlen(answer) != 1 || answer[0] < 'A' || answer[0] > 'D')
            printf("Please enter only A, B, C or D.\n");
    } while (strlen(answer) != 1 || answer[0] < 'A' || answer[0] > 'D');

    strcpy(questions[number], newQuestion);
    for (i = 0; i < 4; i++)
        strcpy(options[number][i], newOptions[i]);
    correctAnswer[number] = answer[0];

    saveQuestions();
    printf("Question updated successfully.\n");
}

static void deletequestion(void)
{
    int number, i;

    printf("\n========== DELETE QUESTION ==========\n");
    if (questionCount == 0)
    {
        printf("There are no questions to delete.\n");
        return;
    }

    viewquestion();
    if (!readNumber("\nEnter question number to delete: ", &number) ||
        number < 1 || number > questionCount)
    {
        printf("Invalid question number.\n");
        return;
    }

    number--;
    for (i = number; i < questionCount - 1; i++)
    {
        strcpy(questions[i], questions[i + 1]);
        memcpy(options[i], options[i + 1], sizeof(options[i]));
        correctAnswer[i] = correctAnswer[i + 1];
    }

    questionCount--;
    saveQuestions();
    printf("Question deleted successfully.\n");
}

static void viewstudents(void)
{
    FILE *fp;
    int id;
    char name[50], username[30];
    int count = 0;

    printf("\n========== REGISTERED STUDENTS ==========\n");
    fp = fopen(STUDENTS_FILE, "r");
    if (fp == NULL)
    {
        printf("No student records found yet.\n");
        return;
    }

    printf("%-10s %-25s %-20s\n", "ID", "NAME", "USERNAME");
    printf("-------------------------------------------------------\n");

    while (fscanf(fp, "%d\n%49[^\n]\n%29s\n", &id, name, username) == 3)
    {
        printf("%-10d %-25s %-20s\n", id, name, username);
        count++;
        /* Skip the password line; it is never displayed. */
        {
            char password[30];
            if (fscanf(fp, "%29s\n", password) != 1)
                break;
        }
    }

    fclose(fp);
    if (count == 0)
        printf("No valid student records found.\n");
    else
        printf("\nTotal registered students: %d\n", count);
}

static void viewresults(void)
{
    FILE *fp;
    int id, score, total, found = 0;
    float percentage;
    int i;
    const char *name;

    printf("\n========== ALL STUDENT RESULTS ==========\n");
    fp = fopen(RESULTS_FILE, "r");
    if (fp == NULL)
    {
        printf("No test results have been recorded yet.\n");
        return;
    }

    printf("%-10s %-24s %-10s %-10s %-12s\n",
           "STUDENT ID", "STUDENT NAME", "SCORE", "TOTAL", "PERCENT");
    printf("---------------------------------------------------------------------\n");

    while (fscanf(fp, "%d|%d|%d|%f", &id, &score, &total, &percentage) == 4)
    {
        name = "Unknown";
        for (i = 0; i < totalStudents; i++)
        {
            if (studentIDs[i] == id)
            {
                name = studentName[i];
                break;
            }
        }

        printf("%-10d %-24.24s %-10d %-10d %8.1f%%\n",
               id, name, score, total, percentage);
        found = 1;
    }

    fclose(fp);
    if (!found)
        printf("No valid results found.\n");
}