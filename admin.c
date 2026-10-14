#include<stdio.h>
#include<string.h>
#include "admin.h"
void adminLogin()
{
  char username[25];
  char password[25];
  printf("Enter Admin Username:");
  scanf("%24s", username);
  printf("Enter Admin Password :");
  scanf("%24s", password);
 if(strcmp(username, "admin") == 0 && strcmp(password, "12345") == 0 )
 {
    printf("Login Suceesful\n");
    adminMenu();
 }
 else
 {
    printf("Invalid Username Or Password\n");

 }

}

 void adminMenu()
 {
    int choice;
    do
    {
    
    printf("\n======ADMIN PANEL==========\n");
    printf("1. Add Question\n");
    printf("2. View Question\n");
    printf("3. Edit Question\n");
    printf("4. Delete Question\n");
    printf("5. View Registered Students\n");
    printf("6. View Student Results\n");
    printf("7.Logout\n");

    printf("Enter Your Choice:");
    scanf("%d", &choice);

    switch (choice)
    {

    case 1:
        printf("Add Questions Selected\n");
        break;

    case 2:
        printf("View Questions Selected\n");
        break;

    case 3:
        printf("Edit Questions Selected\n");
        break;
    
    case 4:
        printf("Delete Question Selected\n");
        break;
    
    case 5:
         printf("View Registered Students\n");
        break;

    case 6:
        printf("View Students Results\n ");
        break;

    case 7:
        printf("Logging Out...");
        break;

    default:
        printf("Invalid Choice");
        
    }
}
    while (choice != 7);
  
 }
