#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "test.h"
#include "question.h"
#include "result.h"

#define TEST_SIZE 10

static void shuffle(int order[], int size)
{
    int i, j, temp;

    for (i = size - 1; i > 0; i--)
    {
        j = rand() % (i + 1);
        temp = order[i];
        order[i] = order[j];
        order[j] = temp;
    }
}

static char readAnswer(void)
{
    char line[30];
    char *p;
    char answer;
    int ch;

    while (1)
    {
        printf("Your answer (A/B/C/D): ");

        if (fgets(line, sizeof(line), stdin) == NULL)
            return 'X';

        if (strchr(line, '\n') == NULL)
            while ((ch = getchar()) != '\n' && ch != EOF) {}

        p = line;
        while (*p == ' ' || *p == '\t')
            p++;

        if (*p == '\n' || *p == '\0')
            continue;

        answer = (char)toupper((unsigned char)*p++);
        while (*p == ' ' || *p == '\t')
            p++;

        if (answer >= 'A' && answer <= 'D' && (*p == '\n' || *p == '\0'))
            return answer;

        printf("Please enter only A, B, C or D.\n");
    }
}

int takeTest(int studentID)
{
    int *order;
    char *answers;
    int total, i, score = 0, questionNumber;
    float percentage;
    static int randomSeeded = 0;

    printf("\n========== ENTRY TEST ==========\n");

    if (questionCount == 0)
    {
        printf("No questions are available. Please contact the admin.\n");
        return -1;
    }

    total = (questionCount < TEST_SIZE) ? questionCount : TEST_SIZE;

    order = malloc(questionCount * sizeof(int));
    answers = calloc(total, sizeof(char));

    if (order == NULL || answers == NULL)
    {
        printf("Unable to allocate memory for the test. Please try again.\n");
        free(order);
        free(answers);
        return -1;
    }

    if (!randomSeeded)
    {
        srand((unsigned int)time(NULL));
        randomSeeded = 1;
    }

    for (i = 0; i < questionCount; i++)
        order[i] = i;

    shuffle(order, questionCount);

    printf("Student ID: %d\n", studentID);
    printf("Total questions: %d\n", total);
    printf("Choose A, B, C or D for each question.\n");

    for (i = 0; i < total; i++)
    {
        questionNumber = order[i];

        printf("\nQuestion %d of %d\n", i + 1, total);
        printf("%s\n", questions[questionNumber]);
        printf("A) %s\n", options[questionNumber][0]);
        printf("B) %s\n", options[questionNumber][1]);
        printf("C) %s\n", options[questionNumber][2]);
        printf("D) %s\n", options[questionNumber][3]);

        answers[i] = readAnswer();

        if (answers[i] == 'X')
        {
            printf("Test cancelled. No result was saved.\n");
            free(order);
            free(answers);
            return -1;
        }

        if (answers[i] == correctAnswer[questionNumber])
            score++;
    }

    percentage = (score * 100.0f) / total;

    printf("\n========== TEST RESULT ==========\n");
    printf("Score      : %d / %d\n", score, total);
    printf("Percentage : %.1f%%\n", percentage);

    if (percentage >= 80)
        printf("Remarks    : Excellent!\n");
    else if (percentage >= 60)
        printf("Remarks    : Good.\n");
    else if (percentage >= 40)
        printf("Remarks    : Average. Keep practising.\n");
    else
        printf("Remarks    : Needs improvement.\n");

    if (score < total)
    {
        printf("\n--- Review of wrong answers ---\n");
        for (i = 0; i < total; i++)
        {
            questionNumber = order[i];
            if (answers[i] != correctAnswer[questionNumber])
            {
                printf("\n%s\n", questions[questionNumber]);
                printf("Your answer   : %c\n", answers[i]);
                printf("Correct answer: %c) %s\n",
                       correctAnswer[questionNumber],
                       options[questionNumber][correctAnswer[questionNumber] - 'A']);
            }
        }
    }

    saveResult(studentID, score, total);
    printf("\nYour result has been saved.\n");

    free(order);
    free(answers);

    return score;
}
