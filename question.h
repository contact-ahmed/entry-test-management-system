#ifndef QUESTION_H
#define QUESTION_H

#define MAX_QUESTIONS 50

extern char questions[MAX_QUESTIONS][200];
extern char options[MAX_QUESTIONS][4][100];
extern char correctAnswer[MAX_QUESTIONS];
extern int questionCount;

void loadQuestions(void);
void saveQuestions(void);
void addquestion(void);
void viewquestion(void);
void editquestion(void);
void deletequestion(void);

#endif
