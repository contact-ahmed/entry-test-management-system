#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "question.h"

#define QUESTIONS_FILE "questions.txt"

char questions[MAX_QUESTIONS][200];
char options[MAX_QUESTIONS][4][100];
char correctAnswer[MAX_QUESTIONS];
int questionCount = 0;

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

static int readFileLine(FILE *fp, char text[], int size)
{
    size_t length;
    int ch;

    if (fgets(text, size, fp) == NULL)
        return 0;

    length = strlen(text);
    if (length > 0 && text[length - 1] == '\n')
        text[length - 1] = '\0';
    else
    {
        while ((ch = fgetc(fp)) != '\n' && ch != EOF) {}
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

static void addSampleQuestions(void)
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

void saveQuestions(void)
{
    FILE *fp;
    int i, j;

    fp = fopen(QUESTIONS_FILE, "w");
    if (fp == NULL)
    {
        printf("Could not save questions. Please check the folder permissions.\n");
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

void loadQuestions(void)
{
    FILE *fp;
    int i, j;
    char answer[10];

    fp = fopen(QUESTIONS_FILE, "r");
    if (fp == NULL)
    {
        addSampleQuestions();
        saveQuestions();
        return;
    }

    questionCount = 0;

    while (questionCount < MAX_QUESTIONS)
    {
        if (!readFileLine(fp, questions[questionCount], sizeof(questions[questionCount])))
            break;
        if (questions[questionCount][0] == '\0')
            break;

        for (j = 0; j < 4; j++)
        {
            if (!readFileLine(fp, options[questionCount][j], sizeof(options[questionCount][j])))
                break;
        }
        if (j != 4)
            break;

        if (!readFileLine(fp, answer, sizeof(answer)))
            break;

        answer[0] = (char)toupper((unsigned char)answer[0]);
        if (strlen(answer) != 1 || answer[0] < 'A' || answer[0] > 'D')
            break;

        correctAnswer[questionCount] = answer[0];
        questionCount++;
    }

    fclose(fp);

    if (questionCount == 0)
    {
        addSampleQuestions();
        saveQuestions();
    }
}

void addquestion(void)
{
    int i;
    char answer[20];

    printf("\n========== ADD QUESTION ==========\n");

    if (questionCount >= MAX_QUESTIONS)
    {
        printf("The question bank is full.\n");
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
            printf("All four options are required. Question was not added.\n");
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
            printf("Please enter A, B, C or D.\n");
    } while (strlen(answer) != 1 || answer[0] < 'A' || answer[0] > 'D');

    correctAnswer[questionCount] = answer[0];
    questionCount++;
    saveQuestions();

    printf("Question added successfully.\n");
}

void viewquestion(void)
{
    int i, j;

    printf("\n========== QUESTION BANK ==========\n");

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

void editquestion(void)
{
    int number, i;
    char newQuestion[200];
    char newOptions[4][100];
    char answer[20];

    printf("\n========== EDIT QUESTION ==========\n");

    if (questionCount == 0)
    {
        printf("There are no questions to edit.\n");
        return;
    }

    viewquestion();

    if (!readNumber("Enter question number: ", &number) ||
        number < 1 || number > questionCount)
    {
        printf("Invalid question number.\n");
        return;
    }

    printf("Enter new question: ");
    if (!readLine(newQuestion, sizeof(newQuestion)) || newQuestion[0] == '\0')
    {
        printf("Question cannot be empty. No changes made.\n");
        return;
    }

    for (i = 0; i < 4; i++)
    {
        printf("Enter new option %c: ", 'A' + i);
        if (!readLine(newOptions[i], sizeof(newOptions[i])) || newOptions[i][0] == '\0')
        {
            printf("All four options are required. No changes made.\n");
            return;
        }
    }

    do
    {
        printf("New correct answer (A/B/C/D): ");
        if (!readLine(answer, sizeof(answer)))
            return;
        if (strlen(answer) == 1)
            answer[0] = (char)toupper((unsigned char)answer[0]);
        if (strlen(answer) != 1 || answer[0] < 'A' || answer[0] > 'D')
            printf("Please enter A, B, C or D.\n");
    } while (strlen(answer) != 1 || answer[0] < 'A' || answer[0] > 'D');

    number--;
    strcpy(questions[number], newQuestion);
    for (i = 0; i < 4; i++)
        strcpy(options[number][i], newOptions[i]);
    correctAnswer[number] = answer[0];

    saveQuestions();
    printf("Question updated successfully.\n");
}

void deletequestion(void)
{
    int number, i;

    printf("\n========== DELETE QUESTION ==========\n");

    if (questionCount == 0)
    {
        printf("There are no questions to delete.\n");
        return;
    }

    viewquestion();

    if (!readNumber("Enter question number to delete: ", &number) ||
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