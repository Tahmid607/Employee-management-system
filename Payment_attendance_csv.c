#include <stdio.h>

#define ATTENDANCE_FILE "attendance.csv"
#define PAYROLL_FILE "payroll.csv"

int main()
{
    int choice;

    int employee_id;
    char employee_name[30];

    char attendance_date[20];
    char attendance_status[20];

    float basic_salary;
    float bonus;
    float total_salary;

    FILE *file;

    printf("===== Taibar Module =====\n");
    printf("1. Attendance\n");
    printf("2. Payroll\n");

    printf("Enter Your Choice: ");

    if (scanf("%d", &choice) != 1)
    {
        printf("\nInvalid Input! Please Enter A Number.\n");
        return 0;
    }

    if (choice == 1)
    {
        printf("\n===== Attendance Module =====\n");

        printf("Enter Employee ID: ");
        if (scanf("%d", &employee_id) != 1)
        {
            printf("Invalid Employee ID!\n");
            return 0;
        }

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
            return 0;
        }

        fprintf(file, "%d,%s,%s,%s\n",
                employee_id,
                employee_name,
                attendance_date,
                attendance_status);

        fclose(file);

        printf("\nAttendance Saved Successfully!\n");
    }
    else if (choice == 2)
    {
        printf("\n===== Payroll Module =====\n");

        printf("Enter Employee ID: ");
        if (scanf("%d", &employee_id) != 1)
        {
            printf("Invalid Employee ID!\n");
            return 0;
        }

        printf("Enter Employee Name: ");
        scanf("%29s", employee_name);

        printf("Enter Basic Salary: ");
        if (scanf("%f", &basic_salary) != 1)
        {
            printf("Invalid Salary!\n");
            return 0;
        }

        printf("Enter Bonus: ");
        if (scanf("%f", &bonus) != 1)
        {
            printf("Invalid Bonus!\n");
            return 0;
        }

        total_salary = basic_salary + bonus;

        printf("\nTotal Salary: %.2f\n", total_salary);

        file = fopen(PAYROLL_FILE, "a");

        if (file == NULL)
        {
            printf("\nUnable To Open Payroll File.\n");
            return 0;
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
    else
    {
        printf("\nInvalid Choice!\n");
    }

    return 0;
}
