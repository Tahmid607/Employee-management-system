#include <stdio.h>
#include <string.h>

#define LOGIN_FILE "login.csv"
#define EMPLOYEE_FILE "employees.csv"
#define ATTENDANCE_FILE "attendance.csv"
#define PAYROLL_FILE "payroll.csv"

int main()
{
    char username[30];
    char password[30];

    char login_username[30];
    char login_password[30];

    int employee_id;
    char employee_name[30];
    int employee_age;
    float employee_salary;

    char attendance_date[20];
    char attendance_status[20];

    float basic_salary;
    float bonus;
    float total_salary;

    int choice;
    int employee_choice;
    int search_id;
    int found;

    FILE *file;

    while (1)
    {
        printf("\n=================================\n");
        printf(" Employee Management System\n");
        printf("=================================\n");
        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. Exit\n");

        printf("Enter Your Choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("\nInvalid Input! Please Enter A Number.\n");

            while (getchar() != '\n')
            {
            }

            continue;
        }

        while (getchar() != '\n')
        {
        }

        if (choice == 1)
        {
            printf("\n===== Employee Registration =====\n");

            printf("Create Username: ");
            scanf("%29s", username);

            printf("Create Password: ");
            scanf("%29s", password);

            file = fopen(LOGIN_FILE, "w");

            if (file == NULL)
            {
                printf("\nUnable To Open Login File.\n");
                continue;
            }

            fprintf(file, "%s,%s\n", username, password);

            fclose(file);

            printf("\nRegistration Successful!\n");
        }

        else if (choice == 2)
        {
            printf("\n===== Employee Login =====\n");

            printf("Enter Username: ");
            scanf("%29s", login_username);

            printf("Enter Password: ");
            scanf("%29s", login_password);

            file = fopen(LOGIN_FILE, "r");

            if (file == NULL)
            {
                printf("\nPlease Register First.\n");
                continue;
            }

            fscanf(file, "%29[^,],%29[^\n]",
                   username, password);

            fclose(file);

            if (strcmp(username, login_username) == 0 &&
                strcmp(password, login_password) == 0)
            {
                printf("\nLogin Successful!\n");

                while (1)
                {
                    printf("\n=================================\n");
                    printf(" Employee Management System\n");
                    printf("=================================\n");
                    printf("1. Employee Management\n");
                    printf("2. Attendance\n");
                    printf("3. Payroll\n");
                    printf("4. Exit\n");

                    printf("Enter Your Choice: ");

                    if (scanf("%d", &choice) != 1)
                    {
                        printf("\nInvalid Input! Please Enter A Number.\n");

                        while (getchar() != '\n')
                        {
                        }

                        continue;
                    }

                    while (getchar() != '\n')
                    {
                    }

                    if (choice == 1)
                    {
                        while (1)
                        {
                            printf("\n===== Employee Management =====\n");
                            printf("1. Add Employee\n");
                            printf("2. View Employees\n");
                            printf("3. Search Employee\n");
                            printf("4. Back\n");

                            printf("Enter Your Choice: ");

                            if (scanf("%d", &employee_choice) != 1)
                            {
                                printf("\nInvalid Input! Please Enter A Number.\n");

                                while (getchar() != '\n')
                                {
                                }

                                continue;
                            }

                            while (getchar() != '\n')
                            {
                            }

                            if (employee_choice == 1)
                            {
                                printf("\n===== Add Employee =====\n");

                                printf("Enter Employee ID: ");
                                scanf("%d", &employee_id);

                                printf("Enter Employee Name: ");
                                scanf("%29s", employee_name);

                                printf("Enter Employee Age: ");
                                scanf("%d", &employee_age);

                                printf("Enter Employee Salary: ");
                                scanf("%f", &employee_salary);

                                file = fopen(EMPLOYEE_FILE, "a");

                                if (file == NULL)
                                {
                                    printf("\nUnable To Open Employee File.\n");
                                    continue;
                                }

                                fprintf(file, "%d,%s,%d,%.2f\n",
                                        employee_id,
                                        employee_name,
                                        employee_age,
                                        employee_salary);

                                fclose(file);

                                printf("\nEmployee Added Successfully!\n");
                            }

                            

                            else if (employee_choice == 2)
                            {
                                file = fopen(EMPLOYEE_FILE, "r");

                                if (file == NULL)
                                {
                                    printf("\nNo Employee Found.\n");
                                    continue;
                                }

                                printf("\n===== Employee List =====\n");

                                while (fscanf(file,
                                              "%d,%29[^,],%d,%f",
                                              &employee_id,
                                              employee_name,
                                              &employee_age,
                                              &employee_salary) == 4)
                                {
                                    printf("\nEmployee ID : %d\n",
                                           employee_id);

                                    printf("Name        : %s\n",
                                           employee_name);

                                    printf("Age         : %d\n",
                                           employee_age);

                                    printf("Salary      : %.2f\n",
                                           employee_salary);
                                }

                                fclose(file);
                            }

                            else if (employee_choice == 3)
                            {
                                printf("\n===== Search Employee =====\n");

                                printf("Enter Employee ID: ");
                                scanf("%d", &search_id);

                                file = fopen(EMPLOYEE_FILE, "r");

                                if (file == NULL)
                                {
                                    printf("\nNo Employee Found.\n");
                                    continue;
                                }

                                found = 0;

                                while (fscanf(file,
                                              "%d,%29[^,],%d,%f",
                                              &employee_id,
                                              employee_name,
                                              &employee_age,
                                              &employee_salary) == 4)
                                {
                                    if (employee_id == search_id)
                                    {
                                        printf("\n===== Employee Found =====\n");
                                        printf("Employee ID : %d\n",
                                               employee_id);

                                        printf("Name        : %s\n",
                                               employee_name);

                                        printf("Age         : %d\n",
                                               employee_age);

                                        printf("Salary      : %.2f\n",
                                               employee_salary);

                                        found = 1;
                                        break;
                                    }
                                }

                                fclose(file);

                                if (found == 0)
                                {
                                    printf("\nEmployee Not Found.\n");
                                }
                            }

                            

                            else if (employee_choice == 4)
                            {
                                break;
                            }

                            else
                            {
                                printf("\nInvalid Choice!\n");
                            }
                        }
                    }

                

                    else if (choice == 2)
                    {
                        printf("\n===== Attendance Module =====\n");

                        printf("Enter Employee ID: ");
                        scanf("%d", &employee_id);

                        printf("Enter Employee Name: ");
                        scanf("%29s", employee_name);

                        printf("Enter Date (DD/MM/YYYY): ");
                        scanf("%19s", attendance_date);

                        printf("Enter Attendance (Present/Absent): ");
                        scanf("%19s", attendance_status);

                        file = fopen(ATTENDANCE_FILE, "a");

                        if (file == NULL)
                        {
                            printf("\nUnable To Open Attendance File.\n");
                            continue;
                        }

                        fprintf(file, "%d,%s,%s,%s\n",
                                employee_id,
                                employee_name,
                                attendance_date,
                                attendance_status);

                        fclose(file);

                        printf("\nAttendance Saved Successfully!\n");
                    }

                    else if (choice == 3)
                    {
                        printf("\n===== Payroll Module =====\n");

                        printf("Enter Employee ID: ");
                        scanf("%d", &employee_id);

                        printf("Enter Employee Name: ");
                        scanf("%29s", employee_name);

                        printf("Enter Basic Salary: ");
                        scanf("%f", &basic_salary);

                        printf("Enter Bonus: ");
                        scanf("%f", &bonus);

                        total_salary = basic_salary + bonus;

                        printf("\nTotal Salary: %.2f\n",
                               total_salary);

                        file = fopen(PAYROLL_FILE, "a");

                        if (file == NULL)
                        {
                            printf("\nUnable To Open Payroll File.\n");
                            continue;
                        }

                        fprintf(file, "%d,%s,%.2f,%.2f,%.2f\n",
                                employee_id,
                                employee_name,
                                basic_salary,
                                bonus,
                                total_salary);

                        fclose(file);

                        printf("\nPayroll Saved Successfully!\n");
                    }

                    else if (choice == 4)
                    {
                        char exit_choice;

                        printf("\nDo You Want To Exit? (Y/N): ");
                        scanf(" %c", &exit_choice);

                        if (exit_choice == 'Y' ||
                            exit_choice == 'y')
                        {
                            printf("\nThank You!\n");
                            return 0;
                        }
                        else if (exit_choice == 'N' ||
                                 exit_choice == 'n')
                        {
                            printf("\nReturning To Main Menu...\n");
                        }
                        else
                        {
                            printf("\nInvalid Input! Please Enter Y or N.\n");
                        }
                    }

                    else
                    {
                        printf("\nInvalid Choice!\n");
                    }
                }
            }
            else
            {
                printf("\nInvalid Username or Password.\n");
            }
        }

        else if (choice == 3)
        {
            char exit_choice;

            printf("\nDo You Want To Exit? (Y/N): ");
            scanf(" %c", &exit_choice);

            if (exit_choice == 'Y' ||
                exit_choice == 'y')
            {
                printf("\nThank You For Using Employee Management System.\n");
                break;
            }
            else if (exit_choice == 'N' ||
                     exit_choice == 'n')
            {
                printf("\nReturning To Main Menu...\n");
            }
            else
            {
                printf("\nInvalid Input! Please Enter Y or N.\n");
            }
        }

        else
        {
            printf("\nInvalid Choice!\n");
        }
    }

    return 0;
}
