#include <stdio.h>
#include <string.h>

int main() {
    char username[20];
    char password[20];
    char login_username[20];
    char login_password[20];
    char employee_name[30];
    int employee_age;
    float employee_salary;
    int choice;

    FILE *fp;
    printf("===== Employee Registration =====");
    printf("Create username: ");
    scanf("%s", username);
    printf("Create password: ");
    scanf("%s", password);

    fp = fopen("login.csv", "w");
    fprintf(fp, "%s %s", username, password);
    fclose(fp);
    printf("Registration successful!");

    printf("===== Employee Login =====");
    printf("Enter username: ");
    scanf("%s", login_username);
    printf("Enter password: ");
    scanf("%s", login_password);

    fp = fopen("login.csv", "r");
    fscanf(fp, "%s %s", username, password);
    fclose(fp);

    if (strcmp(login_username, username) != 0 || strcmp(login_password, password) != 0) {
        printf("Invalid username or password!");

        return 0;
    }

    printf("Login successful!");

    while (1) {
        printf("==============================");
        printf(" Employee Management System");
        printf("==============================");
        printf("1. Add Employee");
        printf("2. View Employees");
        printf("3. Exit");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("Enter employee name: ");
            scanf("%s", employee_name);
            printf("Enter employee age: ");
            scanf("%d", &employee_age);
            printf("Enter employee salary: ");
            scanf("%f", &employee_salary);

            fp = fopen("employee.csv", "a");
            fprintf(fp, "%s %d %.2f", employee_name, employee_age, employee_salary);
            fclose(fp);

            printf("Employee added successfully!");
        } 
        else if (choice == 2) {
            fp = fopen("employee.csv", "r");
            if (fp == NULL) {
                printf("No employees found!");
            } else {
                printf("===== Employee List =====");
                int i = 1;
                while (fscanf(fp, "%s %d %f", employee_name, &employee_age, &employee_salary) != EOF) {
                    printf("Employee %d:", i++);
                    printf("Name: %s", employee_name);
                    printf("Age: %d", employee_age);
                    printf("Salary: %.2f", employee_salary);
                    printf("-------------------------");
                }
                fclose(fp);
            }
        } 
        else if (choice == 3) {
            printf("Thank you for using the Employee Management System.");
            
            break;
        } 
        else {
            printf("Invalid choice! Please try again.");

        }
    }

    return 0;
}
