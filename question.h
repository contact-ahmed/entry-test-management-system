#ifndef QUESTION_H
#define QUESTION_H

#define MAX_QUESTIONS 50

extern char (*questions)[200];
extern char (*options)[4][100];
extern char *correctAnswer;
extern int questionCount;

void loadQuestions(void);
void freeQuestions(void);
void saveQuestions(void);
void addquestion(void);
void viewquestion(void);
void editquestion(void);
void deletequestion(void);

#endif
