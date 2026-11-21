#include <stdio.h>
#include "result.h"

#define RESULTS_FILE "results.txt"

extern char studentName[][50];
extern int studentIDs[];
extern int totalStudents;

void saveResult(int studentID, int score, int total)
{
    FILE *fp;
    float percentage;

    if (total <= 0 || score < 0 || score > total)
    {
        printf("Invalid result. It was not saved.\n");
        return;
    }

    percentage = (score * 100.0f) / total;

    fp = fopen(RESULTS_FILE, "a");
    if (fp == NULL)
    {
        printf("Could not save the result.\n");
        return;
    }

    fprintf(fp, "%d|%d|%d|%.1f\n", studentID, score, total, percentage);
    fclose(fp);
}

void viewStudentResults(int studentID)
{
    FILE *fp;
    int id, score, total, found = 0;
    float percentage;

    printf("\n========== MY TEST RESULTS ==========\n");

    fp = fopen(RESULTS_FILE, "r");
    if (fp == NULL)
    {
        printf("No test results are available yet.\n");
        return;
    }

    while (fscanf(fp, "%d|%d|%d|%f", &id, &score, &total, &percentage) == 4)
    {
        if (id == studentID)
        {
            printf("\nStudent ID      : %d\n", id);
            printf("Correct Answers : %d\n", score);
            printf("Total Questions : %d\n", total);
            printf("Percentage      : %.1f%%\n", percentage);

            if (percentage >= 50.0f)
                printf("Status          : PASS\n");
            else
                printf("Status          : NEEDS IMPROVEMENT\n");

            found = 1;
        }
    }

    fclose(fp);

    if (!found)
        printf("You have not attempted any tests yet.\n");
}

void viewAllResults(void)
{
    FILE *fp;
    int id, score, total, i, found = 0;
    float percentage;
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