#include <stdio.h>

#define EMPLOYEE_FILE "employees.csv"

int main()
{
    int employee_id;
    char employee_name[30];
    char department[30];

    FILE *file;

    printf("===== Department Module =====\n");

    printf("Enter Employee ID: ");

    if (scanf("%d", &employee_id) != 1)
    {
        printf("\nInvalid Employee ID!\n");
        return 0;
    }

    printf("Enter Employee Name: ");
    scanf("%29s", employee_name);

    printf("Enter Department: ");
    scanf("%29s", department);

    file = fopen(EMPLOYEE_FILE, "a");

    if (file == NULL)
    {
        printf("\nUnable To Open Employee File.\n");
        return 0;
    }

    fprintf(file, "%d,%s,%s\n",
            employee_id,
            employee_name,
            department);

    fclose(file);

    printf("\nDepartment Information Saved Successfully!\n");

    return 0;
}
