#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "test.h"

#define TEST_SIZE    10
#define MAX_BANK     200
#define RESULTS_FILE "results.txt"

/* The question bank is defined in admin.c */
extern char questions[][200];
extern char options[][4][100];
extern char correctAnswer[];
extern int  questionCount;

static void shuffle(int arr[], int n)
{
    int i, j, temp;

    for (i = n - 1; i > 0; i--)
    {
        j = rand() % (i + 1);
        temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

static char readAnswer(void)
{
    char line[50];
    char *p;
    char c;
    int ch;

    while (1)
    {
        printf("Your answer (A/B/C/D): ");

        if (fgets(line, sizeof(line), stdin) == NULL)
            return 'X';

        if (strchr(line, '\n') == NULL)
        {
            while ((ch = getchar()) != '\n' && ch != EOF)
            {
            }
        }

        /* skip spaces at the start */
        p = line;
        while (*p == ' ' || *p == '\t')
            p++;

        if (*p == '\n' || *p == '\0')
            continue;

        c = (char)toupper((unsigned char)*p);
        p++;

        /* only spaces may come after the letter */
        while (*p == ' ' || *p == '\t')
            p++;

        if ((c >= 'A' && c <= 'D') && (*p == '\n' || *p == '\0'))
            return c;

        printf("Invalid input! Please type only A, B, C or D.\n");
    }
}

static void saveTestResult(int studentID, int score, int total)
{
    FILE *fp;
    float percentage = (total > 0) ? (score * 100.0f / total) : 0.0f;

    fp = fopen(RESULTS_FILE, "a");
    if (fp == NULL)
    {
        printf("Warning: could not save your result to file.\n");
        return;
    }

    fprintf(fp, "%d|%d|%d|%.1f\n", studentID, score, total, percentage);
    fclose(fp);
}

int takeTest(int studentID)
{
    int order[MAX_BANK];
    char given[TEST_SIZE];
    int bank, total, i, score = 0, q;
    float percentage;
    static int seeded = 0;

    printf("\n====== ENTRY TEST ======\n");

    bank = questionCount;
    if (bank > MAX_BANK)
        bank = MAX_BANK;

    if (bank <= 0)
    {
        printf("No questions are available yet. Please contact the admin.\n");
        return -1;
    }

    if (!seeded)
    {
        srand((unsigned int)time(NULL));
        seeded = 1;
    }

    for (i = 0; i < bank; i++)
        order[i] = i;
    shuffle(order, bank);

    total = (bank < TEST_SIZE) ? bank : TEST_SIZE;

    printf("Student ID: %d\n", studentID);
    printf("Total Questions: %d\n", total);
    printf("Answer each question with A, B, C or D.\n");

    for (i = 0; i < total; i++)
    {
        q = order[i];

        printf("\nQuestion %d of %d\n", i + 1, total);
        printf("%s\n", questions[q]);
        printf("A) %s\n", options[q][0]);
        printf("B) %s\n", options[q][1]);
        printf("C) %s\n", options[q][2]);
        printf("D) %s\n", options[q][3]);

        given[i] = readAnswer();

        if (given[i] == 'X')
        {
            printf("\nInput closed. Test cancelled and not saved.\n");
            return -1;
        }

        if (given[i] == correctAnswer[q])
            score++;
    }

    percentage = score * 100.0f / total;

    printf("\n====== TEST RESULT ======\n");
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
            q = order[i];
            if (given[i] != correctAnswer[q])
            {
                printf("\n%s\n", questions[q]);
                printf("Your answer   : %c\n", given[i]);
                printf("Correct answer: %c) %s\n",
                       correctAnswer[q],
                       options[q][correctAnswer[q] - 'A']);
            }
        }
    }

    saveTestResult(studentID, score, total);
    printf("\nYour result has been saved.\n");

    return score;
}